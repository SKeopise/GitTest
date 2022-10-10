
#include <Key.h>
#include <led.h>


extern int ledpwm,cnt;

int buf = 0;



void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitKEY;
	GPIO_InitKEY.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitKEY.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitKEY.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_InitKEY);
}



unsigned char Key_Driver()
{
	unsigned char KeyNumber = 0;
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0)
		{
			KeyNumber = 1;
			TIM_SetCompare1(TIM2,ledpwm);
			
			if(buf>2)
			cnt = 4;
			
			buf++;
			
			if(buf > 1)
			ledpwm += 1;
			if(ledpwm >= 100)
			{
				break;
			}
			OLED_Clear();
			OLED_ShowNum(3, 1, ledpwm, 3);
			OLED_ShowNum(4, 1, cnt, 1);		
			delay_ms(150);			
		}		
		buf = 0;			
	}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0)
	{
	    delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0)
		{
			KeyNumber = 2;
			TIM_SetCompare1(TIM2,ledpwm);
			
			if(buf>2)
			cnt = 4;
			
			buf++;
			
			if(buf > 1)
			ledpwm -= 1;
			if(ledpwm <= 0)
			{
				break;
			}
			OLED_Clear();
			OLED_ShowNum(3, 1, ledpwm, 3);
			OLED_ShowNum(4, 1, cnt, 1);	
			delay_ms(150);			
		}
		
		buf = 0;
	}
		if(KeyNumber == 1 && cnt != 4)
		{
			TIM_SetCompare1(TIM2,ledpwm);
			cnt = 2;
			
			if(ledpwm < 100)
			{
				ledpwm += 20;
			}
			
			BEEP_ON();     
			delay_ms(200);
			BEEP_OFF();			
		}
		else if(KeyNumber == 2 && cnt != 4)
		{

			TIM_SetCompare1(TIM2,ledpwm);
			cnt = 1;
			
			if(ledpwm > 0)
			{
				ledpwm -= 20;
			}
			
			BEEP_ON();
			delay_ms(200);
			BEEP_OFF();				
		}		
		else if(cnt == 4)
		{
			cnt = 0;
		}		
		
	
    return KeyNumber;
}










