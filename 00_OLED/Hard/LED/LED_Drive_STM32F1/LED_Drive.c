/**
 ******************************************************************************
 * @file    LED_Hard.c
 * @author  LQ
 * @version V3.0
 * @date    2024-11-12
 * @brief   GPIO驱动LED
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
#include "LED_Drive.h"

/**
 * @brief  初始化LED的硬件GPIO接口
 *
 * 本函数旨在配置和初始化指定的GPIO端口和引脚，以驱动LED硬件。
 * 它首先使能相应的GPIO时钟，然后配置GPIO引脚为推挽输出模式。
 *
 * @param GPIO GPIO端口，例如GPIOC
 * @param PIN 需要初始化的GPIO引脚，例如GPIO_Pin_13
 */
void LED_Hard_GPIO_Init(GPIO_PORT_T GPIO, GPIO_PIN_T PIN)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 配置模式
    GPIO_InitTypeDef GPIO_init;
    GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_init.GPIO_Pin = PIN;
    GPIO_Init(GPIO, &GPIO_init);
}

void LED_Hard_Write_Pin(GPIO_PORT_T GPIO, GPIO_PIN_T PIN, uint8_t v)
{
    GPIO_WriteBit(GPIO, PIN, (BitAction)v);
}
