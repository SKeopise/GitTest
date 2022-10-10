#include "stm32f10x.h"                  // Device header
#include <Delay.h>
#include <led.h>
#include <Key.h>
#include <init.h>
#include <Timer.h>
#include <OLED.h>
#include <PWM.h>
#include <lcd.h>
#include <G36_UI.h>
#include <usart.h>    


uint8_t keynumber = 0;

	int cnt=0;
	
	int ledpwm = 0,flag = 0;
	
//	uint8_t RxData;
	
//	int flag_SendByte = 0;


int main()
{
//	OLED_Init();
//	usart_init(9600);
//	Serial_TxPacket[0] = 0x01;
//	Serial_TxPacket[1] = 0x02;
//	Serial_TxPacket[2] = 0x03;
//	Serial_TxPacket[3] = 0x04;
//	Serial_SendPacket();
	
//	Serial_SendByte(0x41);
//	Serial_SendString("$001,3456#");
//	Serial_SendNumber(3232424,7);
//	Serial_SendString("\r\n");	
//	printf("Num = %d\r\n", 666);
//	Serial_Printf("string = %s\r\n","sffafsdasda");
	
	Timer_Init();

	Led_Init();
//	pwm_init();

	BEEP_Init();
//	Key_Init();
	CountSensor_Init();
//	Timer_Init();
	LED1_OFF();
	
//	OLED_ShowChar(1, 1, 'A');
//	OLED_ShowString(2, 1, "asbdjdaw");
//	OLED_ShowNum(3, 1, 3424, 4);
//	OLED_ShowBinNum(4, 1, 0x3f, 8);

	while(1)
	{
//		LED1_OFF();
		
//		if(Serial_GetRxFlag() == 1)
//		{
//			flag_SendByte = 1;
//			RxData = Serial_GetRxData();
//			Serial_SendByte(Serial_RxPacket[0]);
//			OLED_ShowString(2,1,"              ");
//			OLED_ShowString(2,1,RxPacket_Char);			
		}
//		else if(flag_SendByte == 1)
//		{
//			Serial_SendString("\r\n");
//			flag_SendByte = 0;
//		}
		
//		if(ledpwm > 100)
//		{
//			ledpwm = 100;
//			cnt = 3;
//		}
//		else if(ledpwm < 0)
//		{
//			ledpwm = 0;
//			cnt = 0;
//		}
			
//		Delay_ms(20);
//		TIM_SetCompare1(TIM2,ledpwm);	
//		TIM_SetCompare1(TIM2,0);
	

//		G36_UI_Driver();

//		OLED_ShowNum(3, 1, ledpwm, 3);
//		OLED_ShowNum(4, 1, cnt, 1);		

//	}

}


















