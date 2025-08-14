#include "ledDriver.h"

uint16_t _green_pin;
GPIO_TypeDef* _green_port;

void ledDriver_Init(uint16_t pin, GPIO_TypeDef* port){
  _green_pin = pin;
  _green_port = port;
}

void ledDriver_ledOn(){
  HAL_GPIO_WritePin(_green_port, _green_pin, GPIO_PIN_SET);
}

void ledDriver_ledOff(){
  HAL_GPIO_WritePin(_green_port, _green_pin, GPIO_PIN_RESET);
}
