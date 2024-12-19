#ifndef __OLED_H
#define __OLED_H

#include "MyI2C.h"

typedef struct
{
    uint8_t addr; // …Ë±∏µÿ÷∑
    IIC_Device *OLED_IIC;

} OLED_Device;

void OLED_Init(OLED_Device *my_OLED, IIC_Device *OLED_IIC, uint8_t addr);
void OLED_Clear(OLED_Device *my_OLED);
void OLED_ShowChar(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowChinese(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint8_t *str, uint8_t str_l);

#endif
