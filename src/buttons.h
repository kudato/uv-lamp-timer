#pragma once
#include <stdint.h>

#define OK_BUTTON 1
#define UP_BUTTON 2
#define DOWN_BUTTON 3

#define OK_BUTTON_PIN PINC0
#define UP_BUTTON_PIN PINC1
#define DOWN_BUTTON_PIN PINC2

// This value if you use large metal buttons designed for high voltage,
// if you have tactile button, this value can probably be reduced to 25-50
#define DEBOUNCE_DELAY 250


class Button
{
    public:
        static void begin(void);
        static uint8_t pressed(void);
        static bool okButtonState(void);
        static bool upButtonState(void);
        static bool downButtonState(void);
};
