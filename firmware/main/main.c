#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include <lcd.h>
#include <rotary_encoder.h>
#include <control.h>

void app_main(void)
{
    lcd_init();
    lcd_set_dur(300);

    rotary_encoder_init();
    control_init();

    while (1) {
        vTaskDelay(portMAX_DELAY);
    }
}
