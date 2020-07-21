#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/semphr.h>

#include <driver/gpio.h>

#include <lcd.h>
#include <interface.h>
#include <control.h>

void app_main(void)
{
    lcd_init();

    interface_init();
    control_init();

    while (1) {
        vTaskDelay(portMAX_DELAY);
    }
}
