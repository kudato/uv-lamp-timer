#pragma once
#include "../uv-lamp-timer.h"

//--------------------------------------------------------------------
// Class for control UV lamp
//--------------------------------------------------------------------

class UVLamp
{
    public:
        UVLamp(void);
        void setBrightness(uint8_t value);
        void start(void);
        void stop(void);
    private:
        uint8_t _brightness = 0;
};
