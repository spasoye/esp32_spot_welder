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

// TODO: comment this
static void control_task(void* arg);
static void IRAM_ATTR gpio_isr_handler(void* arg);
static void control_pulse(uint16_t on_time, uint16_t off_time, uint8_t num);

void control_init(void)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1<<MOT_CTRL_GPIO);
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

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

static void control_task(void* arg)
{
    uint16_t on_time;
    uint16_t off_time;
    uint16_t pulses;

    for(;;) {
        if(xSemaphoreTake(input_semph, portMAX_DELAY)) {
            printf("Switch pressed\n");
            gpio_intr_disable(SWITCH_GPIO);

            printf("ON: %d\n", on_time);
            printf("OFF: %d\n", off_time);
            printf("NUM: %d\n", pulses);
            
            interface_get_val(&on_time, &off_time, &pulses);

            printf("ON: %d\n", on_time);
            printf("OFF: %d\n", off_time);
            printf("NUM: %d\n", pulses);

            control_pulse(on_time, off_time, pulses);
            
            vTaskDelay(500/portTICK_PERIOD_MS);

            gpio_intr_enable(SWITCH_GPIO);
        }
    }
}

static void control_pulse(uint16_t on_time, uint16_t off_time, uint8_t num)
{
    gpio_set_level(MOT_CTRL_GPIO, 0u);

    for(uint8_t cnt=0; cnt < num; cnt++)
    {
        printf("pulse %d \n", cnt);

        gpio_set_level(MOT_CTRL_GPIO, 1u);
        vTaskDelay(on_time/portTICK_PERIOD_MS);
        gpio_set_level(MOT_CTRL_GPIO, 0u);
        vTaskDelay(off_time/portTICK_PERIOD_MS);
    }

    gpio_set_level(MOT_CTRL_GPIO, 0u);
}

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // TODO: debounce handle
    // Signal the GPIO task.
    xSemaphoreGiveFromISR(input_semph, NULL);
}