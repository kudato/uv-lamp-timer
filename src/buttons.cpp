#pragma once
#include "buttons.h"
#include "buzzer.h"

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------

// State variables
static volatile bool OK_PRESSED = false;
static volatile bool UP_PRESSED = false;
static volatile bool DOWN_PRESSED = false;

// Pressing time for soft debouncing
static volatile uint32_t OK_BUTTON_DEBOUNCE_TIME = 0;
static volatile uint32_t UP_BUTTON_DEBOUNCE_TIME = 0;
static volatile uint32_t DOWN_BUTTON_DEBOUNCE_TIME = 0;

//--------------------------------------------------------------------
// Button events handling
//--------------------------------------------------------------------

// Pin change interrupt
ISR (PCINT1_vect) {
    if (((millis()-OK_BUTTON_DEBOUNCE_TIME) > BUTTON_DEBOUNCE_DELAY)
       && (Button::buttonState(OK_BUTTON_PIN) == true))
    {
        OK_BUTTON_DEBOUNCE_TIME = millis();
        OK_PRESSED = true;
    }

    if (((millis()-UP_BUTTON_DEBOUNCE_TIME) > BUTTON_DEBOUNCE_DELAY)
       && (Button::buttonState(UP_BUTTON_PIN) == true))
    {
        UP_BUTTON_DEBOUNCE_TIME = millis();
        UP_PRESSED = true;
    }

    if (((millis()-DOWN_BUTTON_DEBOUNCE_TIME) > BUTTON_DEBOUNCE_DELAY)
       && (Button::buttonState(DOWN_BUTTON_PIN) == true))
    {
        DOWN_BUTTON_DEBOUNCE_TIME = millis();
        DOWN_PRESSED = true;
    }
}

//--------------------------------------------------------------------
// Setup pins and pin change interrupt
//--------------------------------------------------------------------

void Button::begin(void)
{
    // enable INPUT on A0-A2 pins of the board
    DDRC &= ~((1 << DDC2) | (1 << DDC1) | (1 << DDC0));

    // add PULL_UP on A0-A2 pins of the board
    PORTC |= ((1 << DDC2) | (1 << DDC1) | (1 << DDC0));

    // enable PCIE1 interrupts
    PCICR |= (1 << PCIE1);

    // configure interrupts on A0,A1,A2 pins only
    PCMSK1 |= ((1 << PCINT10) | (1 << PCINT9) | (1 << PCINT8));

    // enable interrupts
    interrupts();
}

//--------------------------------------------------------------------
// Button events handler static class
//--------------------------------------------------------------------

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


bool Button::buttonState(uint8_t button_pin) {
    if ((PINC & (1 << button_pin)) == 0)
    {
        return true;
    }
    return false;
}
