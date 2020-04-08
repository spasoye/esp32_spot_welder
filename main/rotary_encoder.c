#include <math.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "rotary_encoder.h"

#include "lcd.h"

#define ENC_CLK     GPIO_NUM_32
#define ENC_DT      GPIO_NUM_33
#define ENC_SW      27

static QueueHandle_t p_encoder_queue = NULL;
static int16_t duration = 100;

/**
 * @brief  Rotary encoder interrupt service routine. 
 * @note   Debounce protocol should be done here.
 * @param  *arg: pin that triggered the interrupt.
 * @retval None
 */
static void IRAM_ATTR encoder_isr_handler(void *arg);

/**
 * @brief  Task routine that haqndles interrupt events.
 * @note   None.
 * @param  *arg: task arguments. None in this case.
 * @retval None
 */
static void rotary_encoder_task(void *arg);

uint8_t rotary_encoder_init(void)
{
    gpio_config_t io_conf;
    uint8_t ret = 1;

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<ENC_CLK);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL<<ENC_DT);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1<<ENC_SW);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(ENC_CLK, encoder_isr_handler, (void*)ENC_CLK);
    gpio_isr_handler_add(ENC_DT, encoder_isr_handler, (void*)ENC_DT);
    gpio_isr_handler_add(ENC_SW, encoder_isr_handler, (void*)ENC_SW);

    p_encoder_queue = xQueueCreate(1, sizeof(uint32_t));

    ret = (pdPASS ==xTaskCreatePinnedToCore(rotary_encoder_task, "rotary_encoder_task", 2048, NULL, 10, NULL, 0)) ? 0 : 1;

    return ret;
}

void rotary_encoder_int_disable(void)
{
    gpio_intr_disable(ENC_CLK);
    gpio_intr_disable(ENC_DT);
    gpio_intr_disable(ENC_SW);
}

void rotary_encoder_int_enable(void)
{
    gpio_intr_enable(ENC_CLK);
    gpio_intr_enable(ENC_DT);
    gpio_intr_enable(ENC_SW);
}

static void rotary_encoder_task(void *arg)
{
    uint32_t encod_val;
    uint8_t digit_pos = 0;
    uint8_t cursor_pos[] = {4, 1};

    lcd_set_dur(duration);
    lcd_user_pointer(cursor_pos);

    while(true)
    {
        if (xQueueReceive(p_encoder_queue, &encod_val, portMAX_DELAY))
        {
            printf("Interrupt from %d\n", encod_val);
            switch (encod_val)
            {
            case ENC_SW:
                digit_pos = (digit_pos+1)%4;
                cursor_pos[0] = 4-digit_pos;
                printf("Digit: %d\n", digit_pos);
                lcd_user_pointer(cursor_pos);
                break;

            case ENC_DT:
                printf("-\n");
                duration = duration - pow(10, digit_pos);
                break;

            case ENC_CLK:
                printf("+\n");
                duration = duration + pow(10, digit_pos);
                break;

            default:
                break;
            }
            
            // Value can't be smaller than 0;
            if (duration < 0)
            {
                duration = 0;
            }

            // Value can't be larger than 5000 ms.
            if (duration > 5000)
            {
                duration = 5000;
            }

            lcd_set_dur(duration);
            vTaskDelay(50/portTICK_PERIOD_MS);
            gpio_intr_enable(ENC_CLK);
            gpio_intr_enable(ENC_DT);
        }
    }
}

uint16_t rotary_encoder_get_duration(void)
{
    return duration;
}

static void IRAM_ATTR encoder_isr_handler(void *arg)
{
    uint32_t val = (uint32_t) arg;
    
    // TODO: Fix debounce issue.

    if (val == ENC_CLK)
    {
        gpio_intr_disable(ENC_DT);
    }
    else
    {
        gpio_intr_disable(ENC_CLK);
    }
    
    xQueueSendFromISR(p_encoder_queue, &val, NULL);
}