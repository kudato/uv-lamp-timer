#pragma once
#include "display.h"


Display::Display(Adafruit_SSD1306 *driver)
{
    _driver = driver;
}

void Display::begin(void)
{
    _driver->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    _clear();
    _driver->drawBitmap(32, 0, logoImg, 64, 64, 1);
    _display();
    _driver->setFont(&GFX_FONT);
}


void Display::showChoiceScreen(const uint8_t &level)
{
    uint8_t pixelYCursor = 10;
    _clear();
    for (uint8_t i = 0; i < QUANTITY_OF_CONFIGS; i++)
    {
        _driver->setCursor(1,pixelYCursor);
        _driver->setTextSize(1);
        if (level == i)
        {
            _driver->setTextColor(BLACK);
            _driver->drawRect(0, pixelYCursor-11, 128, 14, WHITE);
            _driver->fillRect(0, pixelYCursor-11, 128, 14, WHITE);
        }
        else
        {
            _driver->setTextColor(WHITE);
        }
        _driver->println(Settings::get(i).name);
        pixelYCursor += 15;
    }
    _display();
}

void Display::showPowerScreen(const uint8_t &power)
{
    _clear();
    _driver->setTextColor(WHITE);
    // show header
    _driver->setCursor(0,20);
    _driver->setTextSize(2);
    _driver->println("Power:");
    // show value
    _driver->setCursor(10,55);
    _driver->setTextSize(3);
    _driver->print(power, DEC);
    _driver->println("%");
    // show footer
    _drawArrow();
    _display();
}

void Display::showTimeScreen(const uint32_t &time,
    const uint8_t &cursor)
{
    _clear();
    _driver->setTextColor(WHITE);
    // show header
    _driver->setCursor(0,20);
    _driver->setTextSize(2);
    _driver->println("Time:");
    // show value
    uint16_t minutes;
    uint8_t seconds;
    _calculateTime(time, minutes, seconds);
    _driver->setTextSize(2);
    _driver->setCursor(10,48);
    if (_numsCounter(minutes) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->print(minutes, DEC);
    _driver->print(":");
    if (_numsCounter(seconds) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->println(seconds, DEC);
    // show cursor
    switch (cursor)
    {
    case 0:
        _driver->drawRect(0, 26, 43, 25, WHITE);
        break;
    default:
        _driver->drawRect(56, 26, 43, 25, WHITE);
        break;
    }
    // show footer
    _driver->setCursor(20,64);
    _driver->setTextSize(1);
    _driver->println("min  sec");
    _drawArrow();
    _display();
}


void Display::showSummaryScreen(const ConfigSet &config,
    const uint8_t &cursor)
{
    _clear();
    _driver->setTextColor(WHITE);
    // show light
    _driver->drawBitmap(0, 5, lightImg, 16, 16, WHITE);
    _driver->setCursor(24,21);
    _driver->setTextSize(2);
    _driver->print(config.power, DEC);
    _driver->print("%");

    // show delimeter
    _driver->drawRect(0, 28, 103, 10, WHITE);
    _driver->fillRect(0, 29, 103, 10, WHITE);
    _driver->drawRect(103, 0, 3, 64, WHITE);
    _driver->fillRect(103, 0, 3, 64, WHITE);

    // show time
    _driver->drawBitmap(0, 47, timerImg, 16, 16, WHITE);
    _driver->setCursor(19,63);
    _driver->setTextSize(2);
    uint16_t minutes;
    uint8_t seconds;
    _calculateTime(config.duration, minutes, seconds);
    if (_numsCounter(minutes) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->print(minutes, DEC);
    _driver->print(":");
    if (_numsCounter(seconds) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->print(seconds, DEC);
    // show menu
    _driver->drawBitmap(108, 3, playImg, 16, 16, WHITE);
    _driver->drawBitmap(108, 25, editImg, 16, 16, WHITE);
    _driver->drawBitmap(108, 48, exitImg, 16, 16, WHITE);
    // show cursor
    switch (cursor)
    {
    case 0:
        _driver->drawRect(106, 0, 22, 22, WHITE);
        break;

    case 1:
        _driver->drawRect(106, 22, 22, 22, WHITE);
        break;

    case 2:
        _driver->drawRect(106, 45, 22, 19, WHITE);
        break;
    }
    // show buffer
    _display();
}

void Display::showRunningScreen(const uint32_t &time,
    const uint8_t &cursor, const bool &pause, const bool &hot)
{
    _clear();
    _driver->setTextColor(WHITE);
    // show time
    uint16_t minutes;
    uint8_t seconds;
    _calculateTime(time, minutes, seconds);
    _driver->setCursor(3,33);
    _driver->setTextSize(3);
    if (_numsCounter(minutes) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->print(minutes, DEC);
    _driver->print(":");
    if (_numsCounter(seconds) == 1)
    {
        _driver->print(0, DEC);
    }
    _driver->print(seconds, DEC);
    // show pause btn
    if (pause)
    {
        if (hot)
        {
            _driver->drawBitmap(56, 44, fireImg, 16, 16, WHITE);
            _driver->drawRoundRect(6, 40, 116, 23, 4, WHITE);
        }
        else
        {
            _driver->drawBitmap(27, 44, playImg, 16, 16, WHITE);
            _driver->drawBitmap(87, 44, exitImg, 16, 16, WHITE);
            if (cursor)
            {
                _driver->drawRoundRect(67, 40, 55, 23, 4, WHITE);
            }
            else
            {
                _driver->drawRoundRect(6, 40, 55, 23, 4, WHITE);
            }
        }
    }
    else
    {
        _driver->drawBitmap(56, 44, pauseImg, 16, 16, WHITE);
        _driver->drawRoundRect(6, 40, 116, 23, 4, WHITE);
    }

    // show buffer
    _display();
}


void Display::showDoneScreen(void)
{
    _clear();
    _driver->setTextColor(WHITE);
    // show text
    _driver->setCursor(5,30);
    _driver->setTextSize(3);
    _driver->print("Done!");
    // show ok
    _driver->setCursor(48,60);
    _driver->setTextSize(2);
    _driver->print("Ok");
    _driver->drawRoundRect(6, 38, 110, 25, 4, WHITE);
    // show buffer
    _display();
}





// Draw utilities

void Display::_clear(void)
{
    _driver->clearDisplay();
}

void Display::_display(void)
{
    _driver->display();
}

void Display::_drawArrow(void)
{
    _driver->drawBitmap(110, 28, arrowImg, 16, 16, WHITE);
}


// Others utilities

void Display::_calculateTime(const uint32_t &time,
    uint16_t &minutes, uint8_t &seconds)
{
    minutes = time / MSECONDS_IN_MIN;
    seconds = (time % MSECONDS_IN_MIN) / MSECONDS_IN_SEC;
}


uint8_t Display::_numsCounter(uint8_t number) {
    uint8_t n = 1;
    while ((number/=10) > 0)
    {
        n++;
    }
    return n;
}
