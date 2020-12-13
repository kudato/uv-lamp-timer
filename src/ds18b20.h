#pragma once
#include "../uv-lamp-timer.h"

// Libraries for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//--------------------------------------------------------------------
// Class for getting temperature from sensor DS18B20
//--------------------------------------------------------------------

class TempSensor
{
    public:
        TempSensor(OneWire *bus);
        bool highTemp(void);
        bool needFan(void);
    private:
        OneWire *_bus;
        float _getTemp(void);
        bool _overTemp;
        bool _overThreshold;
        float _temperature;
        uint32_t _prevConversionTime;
};
