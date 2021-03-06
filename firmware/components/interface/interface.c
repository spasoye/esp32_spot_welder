#include <math.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "interface.h"

#include "lcd.h"

#define ENC_CLK     GPIO_NUM_32
#define ENC_DT      GPIO_NUM_33
#define ENC_SW      GPIO_NUM_27

static QueueHandle_t p_encoder_queue = NULL;
static int16_t duration = 100;
static const uint16_t click_debounce = 70;
static const uint16_t long_period = 600;

static int16_t on_time = 50;
static int16_t off_time = 80;
static int8_t pulse_num = 4;
extern interface_property curr_prop = ON_PROP;

/**
 * @brief  Rotary encoder interrupt service routine. 
 * @note   Debounce protocol should be done here.
 * @param  *arg: pin that triggered the interrupt.
 * @retval None
 */
static void IRAM_ATTR encoder_isr_handler(void *arg);

/**
 * @brief  Button interrupt service routine.
 * @note   
 * @param  *arg: 
 * @retval 
 */
static void IRAM_ATTR click_isr_handler(void *arg);

/**
 * @brief  Task routine that haqndles interrupt events.
 * @note   None.
 * @param  *arg: task arguments. None in this case.
 * @retval None
 */
static void interface_task(void *arg);

uint8_t interface_init(void)
{
    gpio_config_t io_conf;
    uint8_t ret = 1;

    // Getting better results when level triggering
    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<ENC_CLK);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1ULL<<ENC_DT);
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
    gpio_isr_handler_add(ENC_SW, click_isr_handler, (void*)ENC_SW);

    p_encoder_queue = xQueueCreate(1, sizeof(encoder_event_t));

    ret = (pdPASS ==xTaskCreate(interface_task, "rotary_encoder_task", 2048, NULL, 10, NULL)) ? 0 : 1;

    return ret;
}

void interface_get_val(uint16_t *p_on_time,uint16_t *p_off_time, uint16_t *p_pulses)
{
    *p_on_time = on_time;
    *p_off_time = off_time;
    *p_pulses = pulse_num;

    return;
}

static void interface_task(void *arg)
{
    encoder_event_t encod_val;
    uint8_t digit_pos = 0;
    uint8_t cursor_pos[] = {2, 1};

    // lcd_user_pointer(cursor_pos, curr_prop);
    
    lcd_set_on(on_time);
    lcd_set_off(off_time);
    lcd_set_num(pulse_num);

    lcd_user_pointer(cursor_pos, curr_prop);

    while(true)
    {
        if (xQueueReceive(p_encoder_queue, &encod_val, portMAX_DELAY))
        {
            switch (encod_val)
            {
            case LONG:
                printf("Long\n");
                curr_prop = (curr_prop + 1) % 3;
                digit_pos = 0;
                
                if (curr_prop == NUM_PROP)
                {
                    cursor_pos[0] = 1 - digit_pos;
                }
                else
                {
                    cursor_pos[0] = 2 - digit_pos;
                }

                lcd_user_pointer(cursor_pos, curr_prop);
                break;

            case SHORT:
                printf("Short\n");

                if (curr_prop == NUM_PROP)
                {
                    digit_pos = (digit_pos+1)%2;
                    cursor_pos[0] = 1 - digit_pos;
                    printf("Digit: %d\n", digit_pos);
                }
                else
                {
                    digit_pos = (digit_pos+1)%3;
                    cursor_pos[0] = 2 - digit_pos;
                    printf("Digit: %d\n", digit_pos);
                }

                lcd_user_pointer(cursor_pos, curr_prop);
                break;

            case CCW:
                switch (curr_prop)
                {
                    case ON_PROP:            
                        on_time = on_time - pow(10, digit_pos);
                        break;
                    
                    case OFF_PROP:            
                        off_time = off_time - pow(10, digit_pos);
                        break;

                    case NUM_PROP:            
                        pulse_num = pulse_num - pow(10, digit_pos);
                        break;

                    default:
                        break;
                }
                break;

            case CW:    
                switch (curr_prop)
                {
                    case ON_PROP:            
                        on_time = on_time + pow(10, digit_pos);
                        break;
                    
                    case OFF_PROP:            
                        off_time = off_time + pow(10, digit_pos);
                        break;

                    case NUM_PROP:            
                        pulse_num = pulse_num + pow(10, digit_pos);
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
            }

            // Values check
            if(on_time > 999) on_time = 999;
            if(off_time > 999) off_time = 999;
            if(pulse_num > 99) pulse_num = 99;

            if(on_time < 0) on_time = 0;
            if(off_time < 0) off_time = 0;
            if(pulse_num < 0) pulse_num = 0;

            lcd_set_on(on_time);
            lcd_set_off(off_time);
            lcd_set_num(pulse_num);

            lcd_user_pointer(cursor_pos, curr_prop);
        }
    }
}

static void IRAM_ATTR encoder_isr_handler(void *arg)
{
    static uint16_t store = 0;
    static uint8_t prevNextCode = 0;
    static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

    encoder_event_t val;

    prevNextCode <<= 2;

    if (!gpio_get_level(ENC_DT)) prevNextCode |= 0x02;
    if (!gpio_get_level(ENC_CLK)) prevNextCode |= 0x01;
    prevNextCode &= 0x0f;

    if  (rot_enc_table[prevNextCode] ) {
        store <<= 4;
        store |= prevNextCode;
        
        if ((store&0xff)==0x2b) 
        {
            val = CW;
            xQueueSendFromISR(p_encoder_queue, &val, NULL);
        }
        if ((store&0xff)==0x17){
            val = CCW;
            xQueueSendFromISR(p_encoder_queue, &val, NULL);
        }
    }
}

static void IRAM_ATTR click_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    uint32_t cur_ms = xTaskGetTickCountFromISR();
    encoder_event_t val;
    static uint32_t last_ms = 0;
    static uint32_t last_up = 0;
    static uint32_t last_down = 0;

    // Debounce handling
    if (click_debounce < ((cur_ms - last_ms) * portTICK_PERIOD_MS))
    {
        if (gpio_get_level(gpio_num))
        {
            if ( (long_period/portTICK_PERIOD_MS) < (cur_ms - last_down) )
            {
                // Longpress
                val = LONG;
            }
            else
            {
                // Shortpress
                val = SHORT;
            }

            xQueueSendFromISR(p_encoder_queue, &val, NULL);
            last_up = cur_ms;
        }
        else
        {
            last_down = cur_ms;
        }
    }

    last_ms = cur_ms;
}