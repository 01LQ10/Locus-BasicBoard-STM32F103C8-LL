#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "OLED.h"

int main()
{
	/* LED Init */
	LED_t LED_PC13, LED_PA15;
	LED_Init(&LED_PC13, GPIOC, GPIO_Pin_13, LED_LIGHT_AT_L);
	LED_Init(&LED_PA15, GPIOA, GPIO_Pin_15, LED_LIGHT_AT_H);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	/*OLED Init*/
	OLED_Init();

	OLED_ShowString(1, 1, "STM32F103C8T6");

	while (1)
	{
		LED_ON(&LED_PA15);
		LED_ON(&LED_PC13);
		Delay_ms(500);

		LED_OFF(&LED_PA15);
		LED_OFF(&LED_PC13);
		Delay_ms(500);
	}
}
