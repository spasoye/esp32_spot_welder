#include "lcd.h"
#include <i2c-lcd1602.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <esp_log.h>
#include <string.h>

#define TAG                     "lcd"
#define I2C_MASTER_NUM           I2C_NUM_0
#define I2C_MASTER_TX_BUF_LEN    0                     // disabled
#define I2C_MASTER_RX_BUF_LEN    0                     // disabled
#define I2C_MASTER_FREQ_HZ       100000
#define I2C_MASTER_SDA_IO        21
#define I2C_MASTER_SCL_IO        22
#define LCD1602_I2C_ADDRESS      0x27

static void i2c_master_init(void);
static i2c_lcd1602_info_t *p_lcd_info;
static uint8_t p_user_pos[2] = {0,0};

extern interface_property curr_prop;

uint8_t lcd_init(void)
{
    uint8_t ret = 1;

    // I2C initialization
    i2c_master_init();
    i2c_port_t i2c_num = I2C_MASTER_NUM;
    uint8_t address = LCD1602_I2C_ADDRESS;

    // SMBus settings
    smbus_info_t * smbus_info = smbus_malloc();

    ret = (ESP_OK == smbus_init(smbus_info, i2c_num, address)) ? 0:1;
    
    if (!ret)
    {
        ret = (ESP_OK == smbus_set_timeout(smbus_info, 1000 / portTICK_RATE_MS)) ? 0:1;
    }

    if (!ret)
    {
        // Set up the LCD1602 device with backlight off
        p_lcd_info = i2c_lcd1602_malloc();
        i2c_lcd1602_init(p_lcd_info, smbus_info, true, 2, 40, 16);
    }

    // Active duration label print
    if (!ret)
    {
        i2c_lcd1602_set_cursor(p_lcd_info, true);
        i2c_lcd1602_move_cursor(p_lcd_info, 0, 0);
        i2c_lcd1602_write_string(p_lcd_info, "on");
        i2c_lcd1602_move_cursor(p_lcd_info, 4, 0);
        i2c_lcd1602_write_string(p_lcd_info, "off");
        i2c_lcd1602_move_cursor(p_lcd_info, 8, 0);
        i2c_lcd1602_write_string(p_lcd_info, "num");
    }

    return ret;
}

uint8_t lcd_set_on(uint16_t dur_val)
{
    uint8_t ret = 1;

    char buff[6];
    snprintf(buff, 6, "%3d", dur_val);
    
    ret = (ESP_OK == i2c_lcd1602_move_cursor(p_lcd_info, 0, 1)) ? 0:1; 
    
    if(!ret)
    {
        ret = (ESP_OK == i2c_lcd1602_write_string(p_lcd_info, buff)) ? 0:1;
        lcd_user_pointer(p_user_pos, curr_prop);
    }

    return ret;
}

uint8_t lcd_set_off(uint16_t dur_val)
{
    uint8_t ret = 1;

    char buff[6];
    snprintf(buff, 6, "%3d", dur_val);
    
    ret = (ESP_OK == i2c_lcd1602_move_cursor(p_lcd_info, 4, 1)) ? 0:1; 
    
    if(!ret)
    {
        ret = (ESP_OK == i2c_lcd1602_write_string(p_lcd_info, buff)) ? 0:1;
        lcd_user_pointer(p_user_pos, curr_prop);
    }

    return ret;
}

uint8_t lcd_set_num(uint8_t num_val)
{
    uint8_t ret = 1;

    char buff[4];
    snprintf(buff, 4, "%2d", num_val);
    
    ret = (ESP_OK == i2c_lcd1602_move_cursor(p_lcd_info, 8, 1)) ? 0:1; 
    
    if(!ret)
    {
        ret = (ESP_OK == i2c_lcd1602_write_string(p_lcd_info, buff)) ? 0:1;
        lcd_user_pointer(p_user_pos, curr_prop);
    }

    return ret;
}

uint8_t lcd_user_pointer(uint8_t *p_pos, interface_property prop)
{
    uint8_t pos[2] = {0,1};

    switch (prop)
    {
        case ON_PROP:
            pos[0] = 0 + p_pos[0];
            break;
        
        case OFF_PROP:
            pos[0] = 4 + p_pos[0];

            break;

        case NUM_PROP:
            pos[0] = 8 + p_pos[0];
            break;

        default:
            break;
    }

    // printf("column: %d row: %d\n", pos[0], pos[1]);
    p_user_pos[0] = p_pos[0];
    p_user_pos[1] = p_pos[1];

    return i2c_lcd1602_move_cursor(p_lcd_info, pos[0], pos[1]);
}

static void i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;  // GY-2561 provides 10kΩ pullups
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;  // GY-2561 provides 10kΩ pullups
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_LEN,
                       I2C_MASTER_TX_BUF_LEN, 0);
}
