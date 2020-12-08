#pragma once
#include <stdint.h>
#include "display.h"
#include "settings.h"
#include "buttons.h"

#define CHOISE_SCREEN 0
#define POWER_SCREEN 1
#define TIME_SCREEN 2
#define SUMMARY_SCREEN 3
#define RUNNING_SCREEN 4
#define DONE_SCREEN 5

extern uint8_t MENU_LEVEL;


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
};
