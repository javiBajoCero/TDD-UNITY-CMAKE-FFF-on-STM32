// unity_uart_output.c
#include "unity_uart_output.h"
#include "usart.h"

void unity_uart_putc(int c)
{
    uint8_t ch = (uint8_t)c;
    HAL_UART_Transmit(&lpuart1, &ch, 1, HAL_MAX_DELAY);
}
