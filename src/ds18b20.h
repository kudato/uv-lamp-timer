#pragma once
#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MAX_TEMP 55.0
#define TEMP_THRESHOLD 35.0
#define TEMP_HYSTERESIS 32.0
#define TEMP_SENSOR_PIN A3
#define TEMP_PRECISION 12
#define TEMP_CONVERSION_TIME 750


class TempSensor
{
    public:
        TempSensor(OneWire *bus);
        bool highTemp(void);
        bool needFan(void);
    private:
        float _getTemp(void);
        OneWire *_bus;
        bool _overTemp;
        bool _overThreshold;
        float _temperature;
        uint32_t _prevConversionTime;
};
