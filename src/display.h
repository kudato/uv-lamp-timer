#pragma once

#include <stdint.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "font.h"
#include "bitmaps.h"
#include "settings.h"

#define GFX_FONT DialogInput_plain_12
#define MSECONDS_IN_MIN 60000
#define MSECONDS_IN_SEC 1000


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

    private:
        Adafruit_SSD1306 *_driver;
        void _clear(void);
        void _display(void);
        void _drawArrow(void);
        uint8_t _numsCounter(uint8_t minutes);
        void _calculateTime(const uint32_t &time,
            uint16_t &minutes, uint8_t &seconds);
};

