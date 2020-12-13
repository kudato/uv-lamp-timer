## UV Lamp Timer

One of my hobbies is making PCB with [photolithography](https://en.wikipedia.org/wiki/Photolithography);
To have an accurate exposure time and be calm during long exposures of the soldering mask, I designed and made this device.

![Device start](hardware/device-start.gif "Device start")

It drives four powerful 1w UV LEDs with a spectrum of 300-400nm and based on Arduino Pro Mini, a DS18B20 temperature sensor, two MOSFET and two voltage converter modules to provide differnt voltage for LEDs and Arduino.

> :warning: **Warning**
> Ultraviolet light, depending on the spectrum, can be harmful or highly harmful and cause permanent eye damage. Use it your own risk and remember to take safety and eye protection. The author is not responsible for any damage that you may cause yourself or others when producing or using this device.

## Features

- Four power and time presets for various technological processes, stored in EEPROM, with changing and saving them from menu without flashing;
- Cooling fan control with hysteresis and overheating protection (if overheating, the timer is paused and continues after the LEDs have cooled);
- Screensaver driven by a sensitive vibration sensor and ADC with a ring buffer to eliminate the influence of vibration from cooling fan.
