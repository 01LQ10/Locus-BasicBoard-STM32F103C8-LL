/**
 ******************************************************************************
 * @file    LED_Hard.c
 * @author  LQ
 * @version V3.0
 * @date    2024-11-12
 * @brief   GPIO����LED
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
#include "LED_Drive.h"

/**
 * @brief  ��ʼ��LED��Ӳ��GPIO�ӿ�
 *
 * ������ּ�����úͳ�ʼ��ָ����GPIO�˿ں����ţ�������LEDӲ����
 * ������ʹ����Ӧ��GPIOʱ�ӣ�Ȼ������GPIO����Ϊ�������ģʽ��
 *
 * @param GPIO GPIO�˿ڣ�����GPIOC
 * @param PIN ��Ҫ��ʼ����GPIO���ţ�����GPIO_Pin_13
 */
void LED_Hard_GPIO_Init(GPIO_PORT_T GPIO, GPIO_PIN_T PIN)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // ����ģʽ
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
