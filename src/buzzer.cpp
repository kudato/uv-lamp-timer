#pragma once
#include "buzzer.h"
#include <stdint.h>
#include <Arduino.h>


static void Buzzer::end(void)
{
    for (int i=400; i<6000; i=i*1.5)
    {
        tone(BUZZER_PIN, i);
        delay(20);
    }
    noTone(BUZZER_PIN);
}

static void Buzzer::click(void)
{
    for (int i=2500; i<6000; i=i*1.5)
    {
        tone(BUZZER_PIN, i);
        delay(10);
    }
    noTone(BUZZER_PIN);
}

static void Buzzer::alarm(void)
{
    for (int j=0; j <3; j++)
    {
        for (int i=1000; i<2000; i=i*1.1)
        {
            tone(BUZZER_PIN, i);
            delay(10);
        }
        delay(50);
        for (int i=1000; i>500; i=i*1.9)
        {
            tone(BUZZER_PIN, i);
            delay(10);
        }
        delay(50);
    }
    noTone(BUZZER_PIN);
}
