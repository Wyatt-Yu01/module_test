#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "usart.h"

void my_printf(char *format,...)
{
    uint8_t buffer[200];
    uint32_t length = 0;
    va_list arg;
    va_start(arg, format);
    length = vsprintf((char *)buffer, format, arg);
    va_end(arg);
    HAL_UART_Transmit_DMA(&huart1, buffer, length);
}
