#pragma once
#include "../uv-lamp-timer.h"

// Button pins
#define OK_BUTTON_PIN PINC0
#define UP_BUTTON_PIN PINC1
#define DOWN_BUTTON_PIN PINC2

//--------------------------------------------------------------------
// Button events handler static class
//--------------------------------------------------------------------

class Button
{
    public:
        static void begin(void);
        static uint8_t pressed(void);
        static bool buttonState(uint8_t);
};
