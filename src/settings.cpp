#pragma once
#include "settings.h"

//--------------------------------------------------------------------
// Presets in EEPROM
//--------------------------------------------------------------------

ConfigSet Settings::get(const uint8_t &number)
{
    ConfigSet readedConfig;
    eeprom_read_block(
        (void*)&readedConfig,
        number * CONFIG_SET_LENGTH - CONFIG_SET_LENGTH,
        CONFIG_SET_LENGTH
    );
    return readedConfig;
}

void Settings::put(const uint8_t &number, const ConfigSet &config)
{
    eeprom_write_block(
        (void*)&config,
        number * CONFIG_SET_LENGTH - CONFIG_SET_LENGTH,
        CONFIG_SET_LENGTH
    );
}

//--------------------------------------------------------------------
// First time init
//--------------------------------------------------------------------

void Settings::init(void)
{
    ConfigSet zero = {0, 0, "Custom"};
    Settings::put(0, zero);

    ConfigSet one = {0, 0, "Photoresist"};
    Settings::put(1, one);

    ConfigSet two = {0, 0, "Solder mask #1"};
    Settings::put(2, two);

    ConfigSet three = {0, 0, "Solder mask #2"};
    Settings::put(3, three);
}
