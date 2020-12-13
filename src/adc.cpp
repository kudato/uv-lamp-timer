#pragma once
#include "adc.h"

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------

// Init global flag for launch screen saver
volatile bool SCREEN_SAVER_STOP = false;

// Ring buffer
static volatile uint8_t RING_BUFFER[RING_BUFFER_SIZE];
static volatile uint8_t RING_BUFFER_IDX_IN = 0;

// Average value calculated from buffer value
static volatile uint8_t ADC_AVERAGE_VALUE = 0;

//--------------------------------------------------------------------
// Conversion complete interrupt
//--------------------------------------------------------------------

ISR (ADC_vect)
{
    // Read value to ring buffer and apply mask to buffer input index
    RING_BUFFER[RING_BUFFER_IDX_IN++] = ADCH;
    RING_BUFFER_IDX_IN &= RING_BUFFER_MASK;
    // When the buffer overflows, recalculate the average value
    if (RING_BUFFER_IDX_IN == 0)
    {
        uint16_t sum = 0;
        for (uint8_t i = 0; i < RING_BUFFER_SIZE; i++)
        {
            sum += RING_BUFFER[i];
        }
        ADC_AVERAGE_VALUE = sum / RING_BUFFER_SIZE;
    }
    // Check trashhold
    if (((ADCH + 255) - ADC_AVERAGE_VALUE) > 355)
    {
        SCREEN_SAVER_STOP = true;
    }
}

//--------------------------------------------------------------------
// Setup ADC in free run mode on A7
//--------------------------------------------------------------------

void adcBegin(void)
{
    // enable adc, auto-triggering, interrupts and set prescaler to 128
    ADCSRA |= ((1 << ADEN) | (1 << ADATE) | (1 << ADIE)
        | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));

    // only ADCH for result read, set reference voltage as VCC
    // and choise A7 as input
    ADMUX &= (~(1 << REFS1) & ~(1 << MUX3));
    ADMUX |= ((1 << REFS0) | (1<<ADLAR) | (1 << MUX2)
        | (1 << MUX1) | (1 << MUX0));

    // start conversions
    ADCSRA |= (1 << ADSC);
}
