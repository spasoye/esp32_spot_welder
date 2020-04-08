#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include "lcd.h"
#include "rotary_encoder.h"

#define GPIO_OUTPUT_0   18
#define GPIO_INPUT_0    16


static SemaphoreHandle_t input_semph = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // Signal the GPIO task.
    xSemaphoreGiveFromISR(input_semph, NULL);
}

static void gpio_task_example(void* arg)
{
    uint16_t duration;

    for(;;) {
        if(xSemaphoreTake(input_semph, portMAX_DELAY)) {
            printf("Button pressed\n");
            gpio_intr_disable(GPIO_INPUT_0);
            
            rotary_encoder_int_disable();
            gpio_set_level(GPIO_OUTPUT_0, 1u);

            duration = rotary_encoder_get_duration();
            
            vTaskDelay(duration/portTICK_PERIOD_MS);
            gpio_set_level(GPIO_OUTPUT_0, 0u);
            vTaskDelay(500/portTICK_PERIOD_MS);

            rotary_encoder_int_enable();
            gpio_intr_enable(GPIO_INPUT_0);
        }
    }
}

void app_main(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1<<GPIO_OUTPUT_0);
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.pin_bit_mask = 1<<GPIO_INPUT_0;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    input_semph = xSemaphoreCreateBinary();
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_INPUT_0, gpio_isr_handler, (void*)GPIO_INPUT_0);

    lcd_init();
    lcd_set_dur(300);

    rotary_encoder_init();

    while (1) {
        vTaskDelay(portMAX_DELAY);
    }
}
