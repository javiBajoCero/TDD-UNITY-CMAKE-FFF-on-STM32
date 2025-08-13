// unity_config.h
#pragma once

// Make Unity call this for every output char:
void unity_uart_putc(int c);

#define UNITY_OUTPUT_CHAR(c)   unity_uart_putc(c)
#define UNITY_INCLUDE_PRINT_FORMATTED   1   // enables printf-style formatting in Unity
