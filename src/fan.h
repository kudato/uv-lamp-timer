#pragma once
#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define FAN_PIN 5
#define FAN_SPEED 255

class Fan {
    public:
        Fan(void);
        bool status(void) const;
        void start(void);
        void stop(void);
    private:
        bool _status;
};

