#pragma once
#include "logic.h"
#include "light.h"
#include "ds18b20.h"
#include "fan.h"
#include "buzzer.h"
#include "adc.h"

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------

// Menu variables
uint8_t MENU_LEVEL = CHOISE_SCREEN;
static uint8_t MENU_CURSOR = 0;

// Configuration variables
static uint8_t CONFIG_NUMBER = 0;
static ConfigSet CHOISED_CONFIG;

// Status variables
static bool RUNNING = false;
static bool RESUMING = false;
static bool SCREEN_SAVER = false;
static bool HIGH_TEMP = false;
static bool PAUSE = false;

// Timers variables
static uint32_t REMAINING_TIME = 0;
static uint32_t LAST_TIME_POINT = 0;
static uint32_t LAST_IDLE_TIME_POINT = 0;

// Done variables
static uint32_t LAST_END_ALARM_TIME_POINT = 0;
static uint8_t END_ALARM_COUNTER = 0;

//--------------------------------------------------------------------
// Periphery objects
//--------------------------------------------------------------------

// Display
static Adafruit_SSD1306 ddriver(128, 64, &Wire, -1);
static Display display(&ddriver);

// DS18B20 temperature sensor
static OneWire oneWire(DS18B20_SENSOR_PIN);
static TempSensor tempSensor(&oneWire);

// PWM lamp control
static UVLamp lamp;

// PWM fan control
static Fan fan;

//--------------------------------------------------------------------
// Peripheral init
//--------------------------------------------------------------------

void Logic::begin(void)
{
    display.begin();
    Button::begin();
    adcBegin();
    if (INITAL_CONFIGS_LOAD == 1)
    {
        Settings::init();
    }
}

//--------------------------------------------------------------------
// Logic for each of the menu levels
//--------------------------------------------------------------------

void Logic::choiseScreen(void)
{
    // Show
    if (!SCREEN_SAVER)
    {
        display.showChoiceScreen(CONFIG_NUMBER);
    }
    else
    {
        return;
    }

    // Button handling
    switch (Button::pressed())
    {
    case OK_BUTTON:
        // read from EEPROM
        CHOISED_CONFIG = Settings::get(CONFIG_NUMBER);

        // Next screen depending on the selected preset
        switch (CONFIG_NUMBER)
        {
        case 0: // if "Custom" then start the setup
            MENU_LEVEL++;
            break;

        default: // else go to SUMMARY_SCREEN
            MENU_LEVEL = SUMMARY_SCREEN;
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
    // Show
    if (!SCREEN_SAVER)
    {
        display.showPowerScreen(CHOISED_CONFIG.power);
    }
    else
    {
        return;
    }

    // Button handling
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
    // Show
    if (!SCREEN_SAVER)
    {
        display.showTimeScreen(CHOISED_CONFIG.duration, MENU_CURSOR);
    }
    else
    {
        return;
    }

    // Button handling
    switch (Button::pressed())
    {
    case OK_BUTTON:
        switch (MENU_CURSOR)
        {
        case 0:
            MENU_CURSOR = 1;
            break;

        default:
            MENU_LEVEL++;
            MENU_CURSOR = 0;
            // write to EEPROM
            Settings::put(CONFIG_NUMBER, CHOISED_CONFIG);
        }
        break;

    case UP_BUTTON:
        if (MENU_CURSOR == 0) // minutes
        {
            if (CHOISED_CONFIG.duration <= 5940000) // 99 min max
            { // +1 min
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration + 60000;
            }
        }
        else if (MENU_CURSOR == 1) // seconds
        {
            if (CHOISED_CONFIG.duration <= 5998000) // 99 min 59 sec max
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration + 1000;
            }
        }
        break;

    case DOWN_BUTTON:
        if (MENU_CURSOR == 0) // minutes
        {
            if (CHOISED_CONFIG.duration >= 60000) // 1 min
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration - 60000;
            }
        } else if (MENU_CURSOR == 1) // seconds
        {
            if (CHOISED_CONFIG.duration >= 2000) // 2 sec
            {
                CHOISED_CONFIG.duration = CHOISED_CONFIG.duration - 1000;
            }
        }
        break;
    }
}


void Logic::summaryScreen(void)
{
    // Show
    if (!SCREEN_SAVER)
    {
        display.showSummaryScreen(CHOISED_CONFIG, MENU_CURSOR);
    }
    else
    {
        return;
    }

    // Button handling
    switch (Button::pressed())
    {
    case OK_BUTTON:
        switch (MENU_CURSOR)
        {
        case 0: // Play
            MENU_LEVEL++;
            REMAINING_TIME = CHOISED_CONFIG.duration;
            break;

        case 1: // Edit
            MENU_LEVEL = POWER_SCREEN;
            break;

        case 2: // Exit
            MENU_LEVEL = CHOISE_SCREEN;
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
    // Start
    if ((!RUNNING || RESUMING) && !HIGH_TEMP)
    {
        lamp.setBrightness(CHOISED_CONFIG.power);
        lamp.start();
        LAST_TIME_POINT = millis();
        RESUMING = false;
        RUNNING = true;
        PAUSE = false;
    }

    // Timer
    if (!PAUSE && !HIGH_TEMP)
    {
        uint32_t timedelta = millis() - LAST_TIME_POINT;
        if (REMAINING_TIME <= timedelta)
        {
            delay(REMAINING_TIME); lamp.stop();
            SCREEN_SAVER_STOP = true;
            REMAINING_TIME = 0;
            RUNNING = false;
            MENU_LEVEL++;
        }
        else
        {
            REMAINING_TIME -= timedelta;
            LAST_TIME_POINT += timedelta;
        }
    }

    // Button handling
    switch (Button::pressed())
    {
    case OK_BUTTON:
        if (MENU_CURSOR == 0)
        {
            if (PAUSE && !HIGH_TEMP)
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
            RUNNING = false;
            PAUSE = false;
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
        SCREEN_SAVER_STOP = true;
        HIGH_TEMP = true;
        Buzzer::alarm();
    }
    else if (!tempSensor.highTemp() && HIGH_TEMP)
    {
        HIGH_TEMP = false;
        RESUMING = true;
    }

    // Show
    if (!SCREEN_SAVER)
    {
        display.showRunningScreen(
            REMAINING_TIME, MENU_CURSOR, PAUSE, HIGH_TEMP);
    }
}


void Logic::doneScreen(void)
{
    // Show
    if (!SCREEN_SAVER)
    {
        display.showDoneScreen();
    }

    // Button handling
    if ((Button::pressed() == OK_BUTTON) && !SCREEN_SAVER)
    {
        MENU_LEVEL = SUMMARY_SCREEN;
        END_ALARM_COUNTER = 0;
    }

    // End alarm
    if ((END_ALARM_COUNTER < 3) && ((END_ALARM_COUNTER == 0)
        || ((millis() - LAST_END_ALARM_TIME_POINT) > 30000)))
    {
        LAST_END_ALARM_TIME_POINT = millis();
        END_ALARM_COUNTER++;
        Buzzer::end();
    }
}

//--------------------------------------------------------------------
// Other logic
//--------------------------------------------------------------------

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


void Logic::screenSaver(void)
{
    if (SCREEN_SAVER_STOP)
    {
        SCREEN_SAVER = false;
        SCREEN_SAVER_STOP = false;
        LAST_IDLE_TIME_POINT = millis();
    }
    else if ((millis() - LAST_IDLE_TIME_POINT) > SCREEN_SAVER_TIMEOUT)
    {
        SCREEN_SAVER = true;
        display.clearScreen();
    }
}
