#include <PWM.h>



void pwm_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitPWM;
	GPIO_InitPWM.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitPWM.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitPWM.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitPWM);
	
	TIM_InternalClockConfig(TIM2);      					//使用内部时钟初始化时基单元
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                       
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;          //指定时钟分频，1为不分频，2为2分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;      //计数器模式，up为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;                      //ARR自动重装器值	/*定时频率=时钟频率/(PSC+1)/(ARR+1)*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;                    //PSC预分频器值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                 //重复计数器值(高级定时器专用)
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);           //配置时基单元
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	                                 //CCR的值
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2,ENABLE);	
	
}

  
















