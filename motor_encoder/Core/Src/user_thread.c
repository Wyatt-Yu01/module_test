
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "user_thread.h"

uint16_t encoder_count;
uint8_t g_10ms_flag;
uint8_t g_50ms_flag;
uint8_t g_100ms_flag;
uint8_t g_500ms_flag;
void user_thread_init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

void user_thread(void)
{
//    my_printf("hello");
    if(g_10ms_flag) {
        encoder_count =  __HAL_TIM_GET_COUNTER(&htim4);
        my_printf("count = %d\r\n", encoder_count);
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        g_10ms_flag = 0;
    }
    if(g_500ms_flag) {
        LED_TOGGLE;
        g_500ms_flag = 0;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t count = 0;
    if(htim->Instance == htim3.Instance ) {
        count++;
        if(0 == count % 10) {
            g_10ms_flag = 1;
        }
        if(0 == count % 50) {
            g_50ms_flag = 1;
        }
        if(0 == count %500) {
            g_500ms_flag = 1;
        }
    }
}

void my_printf(char *format,...)
{
    uint8_t buffer[100];
    va_list arg;
    va_start(arg, format);
    vsprintf((char *)buffer, format, arg);
    va_end(arg);
    HAL_UART_Transmit_DMA(&huart1, buffer, strlen((const char *)buffer));
}