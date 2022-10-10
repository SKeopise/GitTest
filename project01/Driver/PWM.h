#ifndef _PWM_H_
#define _PWM_H_




#include <led.h>

/*
	pwm参数计算公式
	pwm频率 = CK_PSC/(PSC+1)/(ARR+1)
	pwm占空比 = CCR/(ARR+1)
	pwm分辨率 = 1/(ARR+1)
*/




void pwm_init();










#endif
