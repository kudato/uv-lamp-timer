#pragma once
#include "light.h"
#include <stdint.h>
#include <Arduino.h>


UVLamp::UVLamp(void)
{
    pinMode(LED_PWM_PIN,OUTPUT);
}


void UVLamp::setBrightness(uint8_t value)
{
    if (value <= MAX_BRIGHTNESS)
    {
        _brightness = value;
    }
}


void UVLamp::start(void)
{
    analogWrite(LED_PWM_PIN, _brightness);
}

void UVLamp::stop(void)
{
    analogWrite(LED_PWM_PIN, 0);
}
