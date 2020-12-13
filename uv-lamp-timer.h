#pragma once
#include <Arduino.h>

//--------------------------------------------------------------------
// Settings
//--------------------------------------------------------------------

// UV lamp
#define UV_LAMP_PWM_PIN 6
#define UV_LAMP_MAX_BRIGHTNESS 100 // pwm max value in 0-255

// Coolong fan
#define FAN_PIN 5
#define FAN_SPEED 255 // static fan speed

// Temperature control
#define TEMP_STOP_THRESHOLD 55.0 // pause lamp
#define TEMP_FAN_THRESHOLD  35.0 // start fan
#define TEMP_FAN_HYSTERESIS 32.0 // stop fan

// Temperature sensor
#define DS18B20_SENSOR_PIN A3
#define DS18B20_CONVERSION_TIME 750

// Buzzer
#define BUZZER_PIN 9

// This value if you use large metal buttons designed for high voltage,
// if you have tactile button, this value can probably be reduced to 25-50
#define BUTTON_DEBOUNCE_DELAY 250

// Screen saver
#define SCREEN_SAVER_TIMEOUT 30 * MSECONDS_IN_SEC

// Presets
#define INITAL_CONFIGS_LOAD 0

//--------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------

// Time
#define MSECONDS_IN_MIN 60000
#define MSECONDS_IN_SEC 1000

// Buttons
#define OK_BUTTON 1
#define UP_BUTTON 2
#define DOWN_BUTTON 3

// Menu
#define CHOISE_SCREEN 0
#define POWER_SCREEN 1
#define TIME_SCREEN 2
#define SUMMARY_SCREEN 3
#define RUNNING_SCREEN 4
#define DONE_SCREEN 5

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------

// Current menu level variable
extern uint8_t MENU_LEVEL;

// Flag for launch screen saver
extern volatile bool SCREEN_SAVER_STOP;








