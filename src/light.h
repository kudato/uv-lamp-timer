#pragma once
#include <stdint.h>

#define MAX_BRIGHTNESS 100
#define LED_PWM_PIN 6

class UVLamp
{
    public:
        UVLamp(void);
        void setBrightness(uint8_t value);
        void start(void);
        void stop(void);
    private:
        uint8_t _brightness = 0;
};
