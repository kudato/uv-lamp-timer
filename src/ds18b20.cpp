#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "ds18b20.h"


TempSensor::TempSensor(OneWire *bus)
{
    _bus = bus;
    _bus->reset();
    _bus->write(0xCC);
    _bus->write(0x44);
    _prevConversionTime = millis();
    _overThreshold = false;
    _overTemp = false;
}

float TempSensor::_getTemp(void)
{
    if (digitalRead(TEMP_SENSOR_PIN) == 1)
    {
        uint8_t data[2];
        _bus->reset();
        _bus->write(0xCC);
        _bus->write(0xBE);
        data[0] = _bus->read(); data[1] = _bus->read();
        _temperature = ((data[1] << 8) + data[0]) / 16.0;
    }
    if (millis() - _prevConversionTime >= TEMP_CONVERSION_TIME)
    {
        _bus->reset();
        _bus->write(0xCC);
        _bus->write(0x44);
        _prevConversionTime = millis();
    }
    Serial.println(_temperature);
    return _temperature;
}

bool TempSensor::highTemp(void)
{
    if (_getTemp() >= MAX_TEMP)
    {
        _overTemp = true;
        return true;
    }
    else if ((_getTemp() >= TEMP_THRESHOLD) && _overTemp)
    {
        return true;
    }
    _overTemp = false;
    return false;
}


bool TempSensor::needFan(void)
{
    if (_overThreshold)
    {
        if (_getTemp() >= TEMP_HYSTERESIS)
        {
            return true;
        }
    }
    else
    {
        if (_getTemp() >= TEMP_THRESHOLD)
        {
            _overThreshold = true;
            return true;
        }
    }
    _overThreshold = false;
    return false;
}
