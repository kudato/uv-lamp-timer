#pragma once

// Include global variables and settings
#include "../uv-lamp-timer.h"

// Ring buffer settings
#define RING_BUFFER_SIZE 128
#define RING_BUFFER_MASK (RING_BUFFER_SIZE - 1)

// ADC init function
void adcBegin(void);
