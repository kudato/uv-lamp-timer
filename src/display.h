#pragma once
#include "../uv-lamp-timer.h"

// Presets
#include "settings.h"

// Adafruit graphic libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Font and bitmap
#include "bitmaps.h"
#include "font.h"

// Set common font
#define GFX_FONT DialogInput_plain_12

//--------------------------------------------------------------------
// Class for showing all screens
//--------------------------------------------------------------------

class Display
{
    public:
        Display(Adafruit_SSD1306 *driver);
        void begin(void);
        void showChoiceScreen(const uint8_t &level);
        void showPowerScreen(const uint8_t &power);
        void showTimeScreen(const uint32_t &time,
            const uint8_t &cursor);

        void showSummaryScreen(const ConfigSet &config,
            const uint8_t &cursor);

        void showRunningScreen(const uint32_t &time,
            const uint8_t &cursor, const bool &pause, const bool &hot);

        void showDoneScreen(void);

        void clearScreen(void);

    private:
        Adafruit_SSD1306 *_driver;
        void _clear(void);
        void _display(void);
        void _drawArrow(void);
        uint8_t _numsCounter(uint8_t minutes);
        void _calculateTime(const uint32_t &time,
            uint16_t &minutes, uint8_t &seconds);
};
