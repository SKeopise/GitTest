
#include <init.h>

extern int cnt;
int flagled = 0;

void CountSensor_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitSturture;
	GPIO_InitSturture.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSturture.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSturture.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitSturture);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}


void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		BEEP_ON();
		delay_ms(200);
		BEEP_OFF();	
		flagled ^= 1;
//		cnt+=100;
		if(flagled == 1)
		{
			LED1_ON();
		}
		else
		{
			LED1_OFF();
		}

		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}









