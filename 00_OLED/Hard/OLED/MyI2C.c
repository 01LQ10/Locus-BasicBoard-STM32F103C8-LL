#include "MyI2C.h"

void MyI2C_GPIO_Init(GPIO_PORT_T GPIO, GPIO_PIN_T PIN)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIO, &GPIO_InitStructure);
}

void MyI2C_GPIO_Write(GPIO_PORT_T GPIO, GPIO_PIN_T PIN, uint8_t v)
{
	GPIO_WriteBit(GPIO, PIN, (BitAction)v);
}

uint8_t MyI2C_GPIO_Read(GPIO_PORT_T GPIO, GPIO_PIN_T PIN)
{
	return GPIO_ReadInputDataBit(GPIO, PIN);
}


#define MyI2C_W_SDA(v)                             \
	GPIO_WriteBit(myIIC->SDA_port, myIIC->SDA_pin, (BitAction)v); \
	myIIC->delay_us(1)
#define MyI2C_W_SCL(v)                             \
	GPIO_WriteBit(myIIC->SCL_port, myIIC->SCL_pin, (BitAction)v); \
	myIIC->delay_us(1)

#define MyI2C_R_SDA() GPIO_ReadInputDataBit(myIIC->SDA_port, myIIC->SDA_pin)

void MyI2C_Init(IIC_Device *myIIC,
				GPIO_PORT_T SDA_port, GPIO_PIN_T SDA_pin, // SDA引脚定义
				GPIO_PORT_T SCL_port, GPIO_PIN_T SCL_pin, // SCL引脚定义
				void (*delay_us)(unsigned int us))
{
	if (myIIC->IIC_init_state != 1)
		return;
	myIIC->SDA_port = SDA_port;
	myIIC->SDA_pin = SDA_pin;
	myIIC->SCL_port = SCL_port;
	myIIC->SCL_pin = SCL_pin;
	myIIC->delay_us = delay_us;

	MyI2C_GPIO_Init(SDA_port, SDA_pin);
	MyI2C_GPIO_Init(SCL_port, SCL_pin);
	myIIC->IIC_init_state = 1; // 已初始化
}

void MyI2C_Start(IIC_Device *myIIC)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(IIC_Device *myIIC)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(IIC_Device *myIIC, uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SDA((Byte & (0x80 >> i)));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(IIC_Device *myIIC)
{
	uint8_t i, Byte = 0x00;
	MyI2C_W_SDA(1);
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1)
		{
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(IIC_Device *myIIC, uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(IIC_Device *myIIC)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
