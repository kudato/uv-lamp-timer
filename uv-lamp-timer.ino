#include "src/logic.h"

void setup()
{
    Logic::begin();
}

void loop()
{
    Logic::fanControl();
    switch (MENU_LEVEL)
    {
    case CHOISE_SCREEN:
        Logic::choiseScreen();
        break;

    case POWER_SCREEN:
        Logic::powerScreen();
        break;

    case TIME_SCREEN:
        Logic::timeScreen();
        break;

    case SUMMARY_SCREEN:
        Logic::summaryScreen();
        break;

    case RUNNING_SCREEN:
        Logic::runningScreen();
        break;

    case DONE_SCREEN:
        Logic::doneScreen();
        break;
    }
}
