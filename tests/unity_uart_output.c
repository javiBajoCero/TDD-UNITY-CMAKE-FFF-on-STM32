// unity_uart_output.c
#include "main.h"
#include "unity.h"           // pulls in unity_config.h
extern UART_HandleTypeDef huart2; // or your chosen UART

void unity_uart_putc(int c)
{
    uint8_t ch = (uint8_t)c;
    HAL_UART_Transmit(&huart2, &ch, 1, HAL_MAX_DELAY);
}
