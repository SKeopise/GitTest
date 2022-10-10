
#include <led.h>
#include <stdarg.h>

void GPIO_SetInit(int GPIOX,uint16_t GPIO_Pin,...)
{
	va_list valist;
	va_start(valist,GPIO_Pin);
	switch(GPIOX)
	{
		case 'A':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);break;
		case 'B':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);break;
		case 'C':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);break;
		case 'D':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);break;
		case 'E':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);break;
		case 'F':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);break;
		case 'G':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);break;
	}
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = va_arg(valist,GPIOMode_TypeDef);
	switch(GPIO_InitStructure.GPIO_Mode)
	{
		case GPIO_Mode_AIN: break;
		case GPIO_Mode_IN_FLOATING: break;
		case GPIO_Mode_IPD: break;
		case GPIO_Mode_IPU: break;
		case GPIO_Mode_Out_OD: break;
		case GPIO_Mode_Out_PP: break;
		case GPIO_Mode_AF_OD:  break;
		case GPIO_Mode_AF_PP:  break;
		default: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; break;
	}
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	
	GPIO_InitStructure.GPIO_Speed = va_arg(valist,GPIOSpeed_TypeDef);	
	switch(GPIO_InitStructure.GPIO_Speed)
	{
		case GPIO_Speed_10MHz: break;
		case GPIO_Speed_2MHz: break;
		case GPIO_Speed_50MHz: break;
		default: GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; break;
	}	
	va_end(valist);
	
	switch(GPIOX)
	{
		case 'A':GPIO_Init(GPIOA,&GPIO_InitStructure);break;
		case 'B':GPIO_Init(GPIOB,&GPIO_InitStructure);break;
		case 'C':GPIO_Init(GPIOC,&GPIO_InitStructure);break;
		case 'D':GPIO_Init(GPIOD,&GPIO_InitStructure);break;
		case 'E':GPIO_Init(GPIOE,&GPIO_InitStructure);break;
		case 'F':GPIO_Init(GPIOF,&GPIO_InitStructure);break;
		case 'G':GPIO_Init(GPIOG,&GPIO_InitStructure);break;
	}
}



void Led_Init()
{
	GPIO_SetInit('B',GPIO_Pin_5);
	GPIO_SetInit('E',GPIO_Pin_5,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);	
}

void LED1_ON()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_RESET);
}

void LED1_OFF()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_SET);
}

void LED2_ON()
{
	GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_RESET);
}

void LED2_OFF()
{
	GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_SET);
}

void BEEP_Init()
{
	GPIO_SetInit('B',GPIO_Pin_8);
}

void BEEP_ON()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
}

void BEEP_OFF()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
}






