#pragma once
#include <stdint.h>

#define BUZZER_PIN 9


class Buzzer
{
    public:
        static void end(void);
        static void click(void);
        static void alarm(void);
};
