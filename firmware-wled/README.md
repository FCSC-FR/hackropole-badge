# WLED Firmware

<!--
SPDX-FileCopyrightText: 2025 Hackropole
SPDX-License-Identifier: CC-BY-4.0
-->

[WLED](https://kno.wled.ge/) is a opensource firmware to control WS2812 LEDs with a nice Web interface and touch buttons.
WLED is free software under the European Union Public License 1.2.

## Flash firmware

Connect ESP32-S3 USB and make sure you user can write to '/dev/ttyACM0'. Then:
```bash
esptool.py --port /dev/ttyACM0 erase_flash
esptool.py --port /dev/ttyACM0 write_flash 0x0 bootloader.bin
esptool.py --port /dev/ttyACM0 write_flash 0x8000 partitions.bin
esptool.py --port /dev/ttyACM0 write_flash 0x10000 firmware.bin
```

Then reset the board (e.g. by unplugging it).

## Build firmware from sources

If you don't trust our pre-built binaries, you may download and rebuild them from source!

```bash
git clone https://github.com/wled/WLED
# checkout 28 Jun 2025 version, this matchs distributed pre-built binaries
git checkout cc81cc27b033b8358b4acc1f4155d51f31b83f5d
pio run -e esp32s3_4M_qspi -t upload
```

## Initial setup

After successfully flashing the firmware, you should see a new Wi-Fi network `WLED-AP`.
You may connect to this network using the following password: `wled1234`, then you should see a web page "Welcome to WLED!".
You may press "WIFI SETTINGS" to configure now the badge as a Wi-Fi client.

## LED configuration

The Hackropole badge has:
  - 8 WS2812B LED on GPIO 2
  - 1 WS2812B LED on GPIO 21
  - 9 capacitive touch buttons on GPIO 1, 3, 4, 5, 6, 7, 8, 9, 10
  - 2 extra exposed GPIO for user modding

To configure the LED, you should go to `Config > LED Preferences` (or `http://DEVICE_IP/settings/leds`), then in "Hardware setup / LED outputs" configure:
  - Set `Length: 8`, `Data GPIO: 2`
  - Press '+' and set `Length: 1`, `Data GPIO: 21`

![WLED LED Preferences](./wled_led_settings.png)
