// unity_config.h
#pragma once

#include "unity_uart_output.h"

#define UNITY_OUTPUT_CHAR(c)   unity_uart_putc(c)
#define UNITY_INCLUDE_PRINT_FORMATTED   1   // enables printf-style formatting in Unity
