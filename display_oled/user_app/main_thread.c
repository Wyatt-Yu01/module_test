#include "stdint.h"
#include "tim.h"
#include "gpio.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

#define LED_TOGGLE  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)

uint8_t g_5ms_flag;
uint8_t g_10ms_flag;
uint8_t g_20ms_flag;
uint8_t g_50ms_flag;
uint8_t g_100ms_flag;
uint8_t g_200ms_flag;
uint8_t g_500ms_flag;
uint8_t g_1s_flag;

void user_init(void)
{
    ssd1306_Init();
    ssd1306_TestLine();
    HAL_TIM_Base_Start_IT(&htim4);
}
void main_loop(void)
{
    static uint8_t up_key_state = 0;
    static uint8_t set_key_state = 0;
    static uint8_t down_key_state = 0;
    static uint8_t old_up_key_state;
    static uint8_t old_set_key_state;
    static uint8_t old_down_key_state;
    static uint8_t up_key_flag;
    static uint8_t set_key_flag;
    static uint8_t down_key_flag;
    up_key_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    set_key_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
    down_key_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, up_key_state);

    if(old_up_key_state && !up_key_state) {
        up_key_flag = 1;
    }
    else if (!old_up_key_state && up_key_state) {
        up_key_state = 0;
    }
    if(old_set_key_state && !set_key_state) {
        set_key_flag = 1;
    }
    else if (!old_set_key_state && set_key_state) {
        set_key_state = 0;
    }
    if(old_down_key_state && !down_key_state) {
        down_key_flag = 1;
    }
    else if (!old_down_key_state && down_key_state) {
        down_key_state = 0;
    }

    if (g_5ms_flag) {
        g_5ms_flag = 0;
    }
    if (g_10ms_flag) {
        if (up_key_flag) {
//            LED_TOGGLE;
            ssd1306_TestRectangle();
        }
        else if (set_key_flag) {
//            LED_TOGGLE;
            ssd1306_TestArc();
        }
        else if (down_key_flag) {
//            LED_TOGGLE;
            ssd1306_TestFonts();
        }
        g_10ms_flag = 0;
    }
    if (g_20ms_flag) {
        g_20ms_flag = 0;
    }
    if (g_50ms_flag) {
        g_50ms_flag = 0;
    }
    if (g_100ms_flag) {
        g_100ms_flag = 0;
    }
    if (g_200ms_flag) {
        g_200ms_flag = 0;
    }
    if (g_500ms_flag) {
//        LED_TOGGLE;
        g_500ms_flag = 0;
    }
    if (g_1s_flag) {
        g_1s_flag = 0;
    }
    old_up_key_state = up_key_state;
    old_set_key_state = set_key_state;
    old_down_key_state = down_key_state;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t count = 0;
    if(htim4.Instance == htim->Instance) {
        if (0 == count % 5) {
            g_5ms_flag = 1;
        }
        if (0 == count % 10) {
            g_10ms_flag = 1;
        }
        if (0 == count % 20) {
            g_20ms_flag = 1;
        }
        if (0 == count % 50) {
            g_50ms_flag = 1;
        }
        if (0 == count % 100) {
            g_100ms_flag = 1;
        }
        if (0 == count % 200) {
            g_200ms_flag = 1;
        }
        if (0 == count % 500) {
            g_500ms_flag = 1;
        }
        if (0 == count % 1000) {
            g_1s_flag = 1;
        }
        count++;
    }
}


