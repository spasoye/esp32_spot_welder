# Edit following two lines to set component requirements (see docs)
idf_component_register(SRCS main.c
                    INCLUDE_DIRS "."
                    REQUIRES esp32-i2c-lcd1602 esp32-smbus interface control)

