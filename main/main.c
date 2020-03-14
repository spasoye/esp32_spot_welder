#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/queue.h>
#include <driver/gpio.h>

#define GPIO_OUTPUT_0   18
#define GPIO_INPUT_0    16

static QueueHandle_t input_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(input_queue, &gpio_num, NULL);
}

static void gpio_task_example(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(input_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
            gpio_intr_disable(GPIO_INPUT_0);
            gpio_set_level(GPIO_OUTPUT_0, 1u);
            vTaskDelay(300/portTICK_PERIOD_MS);
            gpio_set_level(GPIO_OUTPUT_0, 0u);
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

    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
    io_conf.pin_bit_mask = 1<<GPIO_INPUT_0;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    input_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_INPUT_0, gpio_isr_handler, (void*)GPIO_INPUT_0);
    
    while (1) {
        vTaskDelay(portMAX_DELAY);
    }
}
