#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_


#include "PWM_Config.h"

void PWM_Init(void);
void PWM_Start(PWM_PRESCALER prescaler);
void PWM_Stop(void);
void PWM_SetDuty(PWM_MODE mode, uint8_t dutyCycle);


#endif /* PWM_PRIVATE_H_ */