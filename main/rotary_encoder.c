#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "lcd.h"

#define ENC_CLK     25
#define ENC_DT      26
#define ENC_SW      27

static QueueHandle_t p_encoder_queue = NULL;

static void IRAM_ATTR encoder_isr_handler(void *arg);
static void rotary_encoder_task(void *arg);

uint8_t rotary_encoder_init(void)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1<<ENC_CLK);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1<<ENC_DT);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1<<ENC_SW);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(ENC_CLK, encoder_isr_handler, (void*)ENC_CLK);
    gpio_isr_handler_add(ENC_DT, encoder_isr_handler, (void*)ENC_DT);
    gpio_isr_handler_add(ENC_SW, encoder_isr_handler, (void*)ENC_SW);

    p_encoder_queue = xQueueCreate(10, sizeof(uint8_t));

    xTaskCreate(rotary_encoder_task, "rotary_encoder_task", 2048, NULL, 9, NULL);

    return 0;
}

static void rotary_encoder_task(void *arg)
{
    uint8_t encod_val;

    while(true)
    {
        if (xQueueReceive(p_encoder_queue, &encod_val, portMAX_DELAY))
        {
            printf("jebeno\n");
            lcd_set_dur(encod_val);
        }
    }
}

static void IRAM_ATTR encoder_isr_handler(void *arg)
{
    uint8_t val = (uint8_t) arg;
    xQueueSendFromISR(p_encoder_queue, &val, NULL);
}