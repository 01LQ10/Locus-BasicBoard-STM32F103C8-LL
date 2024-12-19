#ifndef __MYI2C_H
#define __MYI2C_H

#include "stm32f10x.h"

#define GPIO_PORT_T GPIO_TypeDef*
#define GPIO_PIN_T  uint16_t

struct IIC;

typedef struct IIC
{
    // unsigned char addr; // 设备地址
    GPIO_PORT_T SDA_port;
    GPIO_PIN_T SDA_pin;
    GPIO_PORT_T SCL_port;
    GPIO_PIN_T SCL_pin;
    void (*delay_us)(unsigned int us); // 延时函数

    uint8_t IIC_init_state;

    void (*MyI2C_Init)(struct IIC *myIIC,
                       GPIO_PORT_T SDA_port, GPIO_PIN_T SDA_pin,
                       GPIO_PORT_T SCL_port, GPIO_PIN_T SCL_pin,
                       void (*delay_us)(unsigned int us));
    void (*MyI2C_Start)(struct IIC *myIIC);
    void (*MyI2C_Stop)(struct IIC *myIIC);
    void (*MyI2C_SendByte)(struct IIC *myIIC, uint8_t Byte);
    uint8_t (*MyI2C_ReceiveByte)(struct IIC *myIIC);
    void (*MyI2C_SendAck)(struct IIC *myIIC, uint8_t AckBit);
    uint8_t (*MyI2C_ReceiveAck)(struct IIC *myIIC);
} IIC_Device;

void MyI2C_Init(IIC_Device *myIIC,
                GPIO_PORT_T SDA_port, GPIO_PIN_T SDA_pin,
                GPIO_PORT_T SCL_port, GPIO_PIN_T SCL_pin,
                void (*delay_us)(unsigned int us));
void MyI2C_Start(IIC_Device *myIIC);
void MyI2C_Stop(IIC_Device *myIIC);
void MyI2C_SendByte(IIC_Device *myIIC, uint8_t Byte);
uint8_t MyI2C_ReceiveByte(IIC_Device *myIIC);
void MyI2C_SendAck(IIC_Device *myIIC, uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(IIC_Device *myIIC);

#endif
