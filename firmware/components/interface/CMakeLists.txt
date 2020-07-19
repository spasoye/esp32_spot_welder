idf_component_register(SRCS rotary_encoder.c lcd.c
                        INCLUDE_DIRS ./inc
                        REQUIRES esp32-smbus esp32-i2c-lcd1602)