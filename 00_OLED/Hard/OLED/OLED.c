#include "OLED.h"
#include "OLED_Font.h"
#include "Delay.h"


/**
 * @brief  OLED写命令
 * @param  Command 要写入的命令
 * @retval 无
 */
void OLED_WriteCommand(OLED_Device *my_OLED, uint8_t Command)
{
	MyI2C_Start(my_OLED->OLED_IIC);
	MyI2C_SendByte(my_OLED->OLED_IIC, 0x78); // 从机地址
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_SendByte(my_OLED->OLED_IIC, 0x00); // 写命令
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_SendByte(my_OLED->OLED_IIC, Command);
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_Stop(my_OLED->OLED_IIC);
}

/**
 * @brief  OLED写数据
 * @param  Data 要写入的数据
 * @retval 无
 */
void OLED_WriteData(OLED_Device *my_OLED, uint8_t Data)
{
	MyI2C_Start(my_OLED->OLED_IIC);
	MyI2C_SendByte(my_OLED->OLED_IIC, 0x78); // 从机地址
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_SendByte(my_OLED->OLED_IIC, 0x40); // 写数据
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_SendByte(my_OLED->OLED_IIC, Data);
	MyI2C_SendAck(my_OLED->OLED_IIC, 0);
	MyI2C_Stop(my_OLED->OLED_IIC);
}

/**
 * @brief  OLED设置光标位置
 * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
 * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
 * @retval 无
 */
void OLED_SetCursor(OLED_Device *my_OLED, uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(my_OLED, 0xB0 | Y);				  // 设置Y位置
	OLED_WriteCommand(my_OLED, 0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
	OLED_WriteCommand(my_OLED, 0x00 | (X & 0x0F));		  // 设置X位置低4位
}

/**
 * @brief  OLED清屏
 * @param  无
 * @retval 无
 */
void OLED_Clear(OLED_Device *my_OLED)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(my_OLED, j, 0);
		for (i = 0; i < 128; i++)
		{
			OLED_WriteData(my_OLED, 0x00);
		}
	}
}

/**
 * @brief  OLED显示一个字符
 * @param  Line 行位置，范围：1~4
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的一个字符，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowChar(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, char Char)
{
	uint8_t i;
	OLED_SetCursor(my_OLED, (Line - 1) * 2, (Column - 1) * 8); // 设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(my_OLED, OLED_F8x16[Char - ' '][i]); // 显示上半部分内容
	}
	OLED_SetCursor(my_OLED, (Line - 1) * 2 + 1, (Column - 1) * 8); // 设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(my_OLED, OLED_F8x16[Char - ' '][i + 8]); // 显示下半部分内容
	}
}

void OLED_ShowChinese(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint8_t *str, uint8_t str_l)
{
	uint8_t i, j;
	OLED_SetCursor(my_OLED, (Line - 1) * 2, (Column - 1) * 8); // 设置光标位置在上半部分
	for (j = 0; j < str_l; j++)
	{
		for (i = 0; i < 16; i++)
		{
			OLED_WriteData(my_OLED, str[j * 32 + i]); // 显示上半部分内容
		}
	}

	OLED_SetCursor(my_OLED, (Line - 1) * 2 + 1, (Column - 1) * 8); // 设置光标位置在下半部分
	for (j = 0; j < str_l; j++)
	{
		for (i = 0; i < 16; i++)
		{
			OLED_WriteData(my_OLED, str[(j) * 32 + i + 16]); // 显示下半部分内容
		}
	}
}

/**
 * @brief  OLED显示字符串
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  String 要显示的字符串，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowString(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(my_OLED, Line, Column + i, String[i]);
	}
}

/**
 * @brief  OLED次方函数
 * @retval 返回值等于X的Y次方
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
 * @brief  OLED显示数字（十进制，正数）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~4294967295
 * @param  Length 要显示数字的长度，范围：1~10
 * @retval 无
 */
void OLED_ShowNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(my_OLED, Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
 * @brief  OLED显示数字（十进制，带符号数）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：-2147483648~2147483647
 * @param  Length 要显示数字的长度，范围：1~10
 * @retval 无
 */
void OLED_ShowSignedNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(my_OLED, Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(my_OLED, Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(my_OLED, Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
 * @brief  OLED显示数字（十六进制，正数）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
 * @param  Length 要显示数字的长度，范围：1~8
 * @retval 无
 */
void OLED_ShowHexNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(my_OLED, Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(my_OLED, Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief  OLED显示数字（二进制，正数）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
 * @param  Length 要显示数字的长度，范围：1~16
 * @retval 无
 */
void OLED_ShowBinNum(OLED_Device *my_OLED, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(my_OLED, Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
 * @brief  OLED初始化
 * @param  无
 * @retval 无
 */
void OLED_Init(OLED_Device *my_OLED, IIC_Device *OLED_IIC, uint8_t addr)
{
	my_OLED->OLED_IIC = OLED_IIC;
	my_OLED->addr = addr;

	my_OLED->OLED_IIC->delay_us(200);

	// OLED_I2C_Init(); // 端口初始化

	OLED_WriteCommand(my_OLED, 0xAE); // 关闭显示

	OLED_WriteCommand(my_OLED, 0xD5); // 设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(my_OLED, 0x80);

	OLED_WriteCommand(my_OLED, 0xA8); // 设置多路复用率
	OLED_WriteCommand(my_OLED, 0x3F);

	OLED_WriteCommand(my_OLED, 0xD3); // 设置显示偏移
	OLED_WriteCommand(my_OLED, 0x00);

	OLED_WriteCommand(my_OLED, 0x40); // 设置显示开始行

	OLED_WriteCommand(my_OLED, 0xA1); // 设置左右方向，0xA1正常 0xA0左右反置

	OLED_WriteCommand(my_OLED, 0xC8); // 设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(my_OLED, 0xDA); // 设置COM引脚硬件配置
	OLED_WriteCommand(my_OLED, 0x12);

	OLED_WriteCommand(my_OLED, 0x81); // 设置对比度控制
	OLED_WriteCommand(my_OLED, 0xCF);

	OLED_WriteCommand(my_OLED, 0xD9); // 设置预充电周期
	OLED_WriteCommand(my_OLED, 0xF1);

	OLED_WriteCommand(my_OLED, 0xDB); // 设置VCOMH取消选择级别
	OLED_WriteCommand(my_OLED, 0x30);

	OLED_WriteCommand(my_OLED, 0xA4); // 设置整个显示打开/关闭

	OLED_WriteCommand(my_OLED, 0xA6); // 设置正常/倒转显示

	OLED_WriteCommand(my_OLED, 0x8D); // 设置充电泵
	OLED_WriteCommand(my_OLED, 0x14);

	OLED_WriteCommand(my_OLED, 0xAF); // 开启显示

	OLED_Clear(my_OLED); // OLED清屏
}
