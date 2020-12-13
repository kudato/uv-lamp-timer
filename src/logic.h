#pragma once
#include "../uv-lamp-timer.h"

#include "display.h"
#include "settings.h"
#include "buttons.h"

//--------------------------------------------------------------------
// Handling buttons, menu, display, cooling and timers
//--------------------------------------------------------------------

class Logic
{
    public:
        static void begin(void);
        static void choiseScreen(void);
        static void powerScreen(void);
        static void timeScreen(void);
        static void summaryScreen(void);
        static void runningScreen(void);
        static void doneScreen(void);
        static void fanControl(void);
        static void screenSaver(void);
};
