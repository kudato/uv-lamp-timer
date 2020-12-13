#pragma once
#include "light.h"

//--------------------------------------------------------------------
// Class for control UV lamp
//--------------------------------------------------------------------

UVLamp::UVLamp(void)
{
    pinMode(UV_LAMP_PWM_PIN,OUTPUT);
}


void UVLamp::setBrightness(uint8_t value)
{
    if (value <= UV_LAMP_MAX_BRIGHTNESS)
    {
        _brightness = value;
    }
}


void UVLamp::start(void)
{
    analogWrite(UV_LAMP_PWM_PIN, _brightness);
}


void UVLamp::stop(void)
{
    analogWrite(UV_LAMP_PWM_PIN, 0);
}
