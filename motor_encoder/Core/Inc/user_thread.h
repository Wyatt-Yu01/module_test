#ifndef __USER_THREAD_H__
#define __USER_THREAD_H__

#define LED_TOGGLE  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)

void user_thread(void);
void user_thread_init(void);
void my_printf(char *format,...);


#endif
