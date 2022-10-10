#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"                  // Device header

#include <stdio.h>

#include <stdarg.h>



extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];
extern char RxPacket_Char[];


void usart_init(u32 bound);

void Serial_SendByte(uint8_t Byte);

void Serial_SendArray(uint8_t *Array,uint16_t Length);

void Serial_SendString(char *Array);

void Serial_SendNumber(uint32_t Number,uint8_t Length);

void Serial_Printf(char* format,...);

//uint8_t Serial_GetRxData();

uint8_t Serial_GetRxFlag();

void Serial_SendPacket();

void Hex_RxData();

void String_RxData();



#endif