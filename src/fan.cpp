#pragma once
#include "fan.h"
#include <stdint.h>
#include <Arduino.h>

Fan::Fan(void)
{
    pinMode(FAN_PIN, OUTPUT);
}

bool Fan::status(void) const
{
    return _status;
}

void Fan::start(void)
{
    analogWrite(FAN_PIN, FAN_SPEED);
    _status = true;
}

void Fan::stop(void)
{
    analogWrite(FAN_PIN, 0);
    _status = false;
}

