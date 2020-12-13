#pragma once
#include "../uv-lamp-timer.h"

//--------------------------------------------------------------------
// Presets in EEPROM
//--------------------------------------------------------------------

#define CONFIG_SET_LENGTH 20
#define QUANTITY_OF_CONFIGS 4


struct ConfigSet
{
    uint8_t power;     // 1 byte
    uint32_t duration; // 4 byte
    char name[15];     // 14 byte
};


class Settings
{
    public:
        static void init(void); // Used for initial configuration load
        static ConfigSet get(const uint8_t &number);
        static void put(const uint8_t &number, const ConfigSet &config);
};
