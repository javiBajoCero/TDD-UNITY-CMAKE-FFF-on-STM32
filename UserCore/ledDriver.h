#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "main.h"

// Add your function declarations and types here
void ledDriver_Init(uint16_t pin, GPIO_TypeDef* port);
void ledDriver_ledOn();
void ledDriver_ledOff();

#endif // LEDDRIVER_H