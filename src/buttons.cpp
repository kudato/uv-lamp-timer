#pragma once
#include "buttons.h"
#include "buzzer.h"
#include <Arduino.h>

static volatile bool OK_PRESSED = false;
static volatile bool UP_PRESSED = false;
static volatile bool DOWN_PRESSED = false;

static volatile uint32_t OK_BUTTON_DEBOUNCE_TIME = 0;
static volatile uint32_t UP_BUTTON_DEBOUNCE_TIME = 0;
static volatile uint32_t DOWN_BUTTON_DEBOUNCE_TIME = 0;


ISR (PCINT1_vect) {
    if (((millis()-OK_BUTTON_DEBOUNCE_TIME) > DEBOUNCE_DELAY)
       && (Button::okButtonState() == true))
    {
        OK_BUTTON_DEBOUNCE_TIME = millis();
        OK_PRESSED = true;
    }

    if (((millis()-UP_BUTTON_DEBOUNCE_TIME) > DEBOUNCE_DELAY)
       && (Button::upButtonState() == true))
    {
        UP_BUTTON_DEBOUNCE_TIME = millis();
        UP_PRESSED = true;
    }

    if (((millis()-DOWN_BUTTON_DEBOUNCE_TIME) > DEBOUNCE_DELAY)
       && (Button::downButtonState() == true))
    {
        DOWN_BUTTON_DEBOUNCE_TIME = millis();
        DOWN_PRESSED = true;
    }
}


bool Button::okButtonState(void) {
    if ((PINC & (1 << OK_BUTTON_PIN)) == 0)
    {
        return true;
    }
    return false;
}

bool Button::upButtonState(void)  {
    if ((PINC & (1 << UP_BUTTON_PIN)) == 0)
    {
        return true;
    }
    return false;
}

bool Button::downButtonState(void)  {
    if ((PINC & (1 << DOWN_BUTTON_PIN)) == 0)
    {
        return true;
    }
    return false;
}


void Button::begin(void)
{
    // enable INPUT on A0-A2 pins of the board
    DDRC &= ~(
        (1 << DDC2) |
        (1 << DDC1) |
        (1 << DDC0)
    );
    // add PULL_UP on A0-A2 pins of board
    PORTC |= (
        (1 << DDC2) |
        (1 << DDC1) |
        (1 << DDC0)
    );
    // enable PCIE1 interrupts
    PCICR |= (1 << PCIE1);
    // configure interrupts on A0,A1,A2 pins only
    PCMSK1 |= ((1 << PCINT10) | (1 << PCINT9) | (1 << PCINT8));
    // enable interrupts
    interrupts();
}


uint8_t Button::pressed(void)
{
    if (UP_PRESSED)
    {
        UP_PRESSED=false;
        Buzzer::click();
        return UP_BUTTON;
    }
    if (DOWN_PRESSED)
    {
        DOWN_PRESSED=false;
        Buzzer::click();
        return DOWN_BUTTON;
    }
    if (OK_PRESSED)
    {
        OK_PRESSED=false;
        Buzzer::click();
        return OK_BUTTON;
    }
    return 0;
}
