
#include <Timer.h>


extern int cnt;

void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);      					//使用内部时钟初始化时基单元
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                       
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;          //指定时钟分频，1为不分频，2为2分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;      //计数器模式，up为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;                      //ARR自动重装器值	/*定时频率=时钟频率/(PSC+1)/(ARR+1)*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;                    //PSC预分频器值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                 //重复计数器值(高级定时器专用)
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);           //配置时基单元
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                     //使能定时器中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);	
}



void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
//			BEEP_ON();
//			delay_ms(200);
//			BEEP_OFF();	
//			cnt++;
	
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}















