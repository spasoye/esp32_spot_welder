#include <control.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include "lcd.h"
#include "interface.h"

#define MOT_CTRL_GPIO   18
#define SWITCH_GPIO     16

static SemaphoreHandle_t input_semph = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // TODO: debounce handle
    // Signal the GPIO task.
    xSemaphoreGiveFromISR(input_semph, NULL);
}

static void control_task(void* arg)
{
    uint16_t duration;

    for(;;) {
        if(xSemaphoreTake(input_semph, portMAX_DELAY)) {
            printf("Switch pressed\n");
            gpio_intr_disable(SWITCH_GPIO);
            
            gpio_set_level(MOT_CTRL_GPIO, 1u);

            duration = interface_get_duration();
            
            vTaskDelay(duration/portTICK_PERIOD_MS);
            gpio_set_level(MOT_CTRL_GPIO, 0u);
            vTaskDelay(500/portTICK_PERIOD_MS);

            gpio_intr_enable(SWITCH_GPIO);
        }
    }
}

void control_init(void)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.pin_bit_mask = 1<<SWITCH_GPIO;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    input_semph = xSemaphoreCreateBinary();
    xTaskCreate(control_task, "control_task", 2048, NULL, 10, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(SWITCH_GPIO, gpio_isr_handler, (void*)SWITCH_GPIO);
}