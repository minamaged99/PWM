#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_


#include "CPU_Config.h"
#include "PWM_Address.h"

//Table 40
typedef enum
{
	Disconnected = 0,
	Inverting = 1,
	Non_Inverting = 2
}PWM_MODE;

// Table 42
typedef enum
{
	PWM_No_Prescaling = 0,
	PWM_8 = 1,
	PWM_64 = 2,
	PWM_256 = 3,
	PWM_1024 = 4
}PWM_PRESCALER;


#endif /* PWM_CONFIG_H_ */