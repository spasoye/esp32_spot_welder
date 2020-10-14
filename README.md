# ESP spot welder control

MOT spot welder controller based on ESP32 microcontroller.
 
Basically it is configurable pulse generator. 
User can configure pulse's ON and OFF time and number of pulses that will be generated when the switch is pressed.
Solid state relay is then switched on and off

User interface is implemented using rotary encoder and [16x2 LCD display](https://github.com/DavidAntliff/esp32-i2c-lcd1602).

## Build and flash
```bash
git clone git@github.com:spasoye/esp32_spot_welder.git
```

Build using make:
```bash
cd esp32_spot_welder/firmware
make all -j 8
make flash
```

Build usin *idf.py* tool:
```bash
idf.py build flash
```

## Links
https://github.com/DavidAntliff/esp32-i2c-lcd1602

## Status

Active
