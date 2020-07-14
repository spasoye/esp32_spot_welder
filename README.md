# ESP spot welder control

Firmware for spot welder relay controller based on ESP32 dev kit.

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

## Status

Active
