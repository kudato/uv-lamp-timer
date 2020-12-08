#pragma once
#include "logic.h"
#include "light.h"
#include "ds18b20.h"
#include "fan.h"
#include "buzzer.h"
#include <Arduino.h>

uint8_t MENU_LEVEL = 0;

static Adafruit_SSD1306 ddriver(128, 64, &Wire, -1);
static Display display(&ddriver);

static OneWire oneWire(TEMP_SENSOR_PIN);
static TempSensor tempSensor(&oneWire);

static UVLamp lamp;
static Fan fan;

static uint8_t MENU_CURSOR = 0;
static uint8_t CONFIG_NUMBER = 0;
static ConfigSet CHOISED_CONFIG;

static bool RUNNING = false;
static bool RESUMING = false;
static uint32_t REMAINING_TIME = 0;
static uint32_t LAST_TIME_POINT = 0;
static bool HIGH_TEMP = false;
static bool PAUSE = false;


void Logic::begin(void)
{
    display.begin();
    Button::begin();
}


void Logic::choiseScreen(void)
{
    display.showChoiceScreen(CONFIG_NUMBER);
    switch (Button::pressed())
    {
    case OK_BUTTON:
        CHOISED_CONFIG = Settings::get(CONFIG_NUMBER);
        switch (CONFIG_NUMBER)
        {
        case 0:
            MENU_LEVEL++;
            break;

        default:
            MENU_LEVEL = 3;
            break;
        }
        break;

    case DOWN_BUTTON:
        if (CONFIG_NUMBER < (QUANTITY_OF_CONFIGS-1))
        {
            CONFIG_NUMBER++;
        }
        break;

    case UP_BUTTON:
        if (CONFIG_NUMBER > 0)
        {
            CONFIG_NUMBER--;
        }
        break;
    }
}


void Logic::powerScreen(void)
{
    display.showPowerScreen(CHOISED_CONFIG.power);
    switch (Button::pressed())
    {
    case OK_BUTTON:
        Settings::put(CONFIG_NUMBER, CHOISED_CONFIG);
        MENU_LEVEL++;
        break;

    case UP_BUTTON:
        if (CHOISED_CONFIG.power <= 90)
        {
            CHOISED_CONFIG.power = CHOISED_CONFIG.power + 10;
        }
        break;

    case DOWN_BUTTON:
        if (CHOISED_CONFIG.power >= 10)
        {
            CHOISED_CONFIG.power = CHOISED_CONFIG.power - 10;
        }
        break;
    }
}


void Logic::timeScreen(void)
{
    display.showTimeScreen(CHOISED_CONFIG.duration, MENU_CURSOR);
    switch (Button::pressed())
    {
    case OK_BUTTON:
        if (MENU_CURSOR == 0)
        {
            MENU_CURSOR = 1;
        }
        else
        {
            MENU_CURSOR = 0;
            Settings::put(CONFIG_NUMBER, CHOISED_CONFIG);
            MENU_LEVEL++;
        }
        break;

    case UP_BUTTON:
        if (MENU_CURSOR == 0)
        {
            if (CHOISED_CONFIG.duration <= 5940000)
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration + 60000;
            }
        }
        else if (MENU_CURSOR == 1)
        {
            if (CHOISED_CONFIG.duration <= 5998000)
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration + 1000;
            }
        }
        break;

    case DOWN_BUTTON:
        if (MENU_CURSOR == 0)
        {
            if (CHOISED_CONFIG.duration >= 60000)
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration - 60000;
            }
        } else if (MENU_CURSOR == 1)
        {
            if (CHOISED_CONFIG.duration >= 2000)
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration - 1000;
            }
        }
        break;
    }
}


void Logic::summaryScreen(void)
{
    display.showSummaryScreen(CHOISED_CONFIG, MENU_CURSOR);
    switch (Button::pressed())
    {
    case OK_BUTTON:
        switch (MENU_CURSOR)
        {
        case 0:
            MENU_LEVEL++;
            REMAINING_TIME = CHOISED_CONFIG.duration;
            break;

        case 1:
            MENU_LEVEL = 1;
            break;

        case 2:
            MENU_LEVEL = 0;
            break;
        }
        MENU_CURSOR = 0;

    case UP_BUTTON:
        if (MENU_CURSOR > 0)
        {
            MENU_CURSOR--;
        }
        break;

    case DOWN_BUTTON:
        if (MENU_CURSOR < 2)
        {
            MENU_CURSOR++;
        }
        break;
    }
}


void Logic::runningScreen(void)
{
    if (REMAINING_TIME < (CHOISED_CONFIG.duration - 500))
    {
        display.showRunningScreen(
            REMAINING_TIME, MENU_CURSOR, PAUSE, HIGH_TEMP);
    }
    // Start
    if (!RUNNING || RESUMING)
    {
        lamp.setBrightness(CHOISED_CONFIG.power);
        lamp.start();
        LAST_TIME_POINT = millis();
        RESUMING = false;
        RUNNING = true;
        PAUSE = false;
    }

    // Timer
    if (!PAUSE)
    {
        uint32_t timedelta = millis() - LAST_TIME_POINT;
        if (REMAINING_TIME <= timedelta)
        {
            delay(REMAINING_TIME); lamp.stop();
            Buzzer::end(); RUNNING = false;
            REMAINING_TIME = 0;
            MENU_LEVEL++;
        }
        else
        {
            REMAINING_TIME = REMAINING_TIME - timedelta;
            LAST_TIME_POINT = LAST_TIME_POINT + timedelta;
        }
    }

    // Pause handling
    switch (Button::pressed())
    {
    case OK_BUTTON:
        if (MENU_CURSOR == 0)
        {
            if (PAUSE)
            {
                PAUSE = false;
                RESUMING = true;
            }
            else
            {
                PAUSE = true;
                lamp.stop();
            }
        }
        else
        {
            MENU_LEVEL = SUMMARY_SCREEN;
            MENU_CURSOR = 0;
        }
        break;
    case 0:
        break;
    default:
        if (PAUSE)
        {
            if (MENU_CURSOR == 1)
            {
                MENU_CURSOR = 0;
            }
            else
            {
                MENU_CURSOR = 1;
            }
        }
        break;
    }

    // High temp
    if (tempSensor.highTemp() && !HIGH_TEMP)
    {
        PAUSE = true; lamp.stop();
        HIGH_TEMP = true;
        Buzzer::alarm();
    }
    else if (HIGH_TEMP)
    {
        HIGH_TEMP = false;
        RESUMING = true;
    }
}


void Logic::doneScreen(void)
{
    display.showDoneScreen();
    if (Button::pressed() == OK_BUTTON)
    {
        MENU_LEVEL = 3;
    }
}


void Logic::fanControl(void)
{
    if (tempSensor.needFan() && !fan.status())
    {
        fan.start();
    }
    if (!tempSensor.needFan() && fan.status())
    {
        fan.stop();
    }
}
