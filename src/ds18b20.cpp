#pragma once
#include "ds18b20.h"

//--------------------------------------------------------------------
// Class for getting temperature from sensor DS18B20
//--------------------------------------------------------------------

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


bool TempSensor::needFan(void)
{
    if (_overThreshold)
    {
        if (_getTemp() >= TEMP_FAN_HYSTERESIS)
        {
            return true;
        }
    }
    else
    {
        if (_getTemp() >= TEMP_FAN_THRESHOLD)
        {
            _overThreshold = true;
            return true;
        }
    }
    _overThreshold = false;
    return false;
}


bool TempSensor::highTemp(void)
{
    if (_getTemp() >= TEMP_STOP_THRESHOLD)
    {
        _overTemp = true;
        return true;
    }
    else if ((_getTemp() >= TEMP_FAN_THRESHOLD) && _overTemp)
    {
        return true;
    }
    _overTemp = false;
    return false;
}


float TempSensor::_getTemp(void)
{
    if (digitalRead(DS18B20_SENSOR_PIN) == 1)
    {
        uint8_t data[2];
        _bus->reset();
        _bus->write(0xCC);
        _bus->write(0xBE);
        data[0] = _bus->read(); data[1] = _bus->read();
        _temperature = ((data[1] << 8) + data[0]) / 16.0;
    }
    if (millis() - _prevConversionTime >= DS18B20_CONVERSION_TIME)
    {
        _bus->reset();
        _bus->write(0xCC);
        _bus->write(0x44);
        _prevConversionTime = millis();
    }
    return _temperature;
}
