#include "PWM_Private.h"

void PWM_Init(void)
{
	// Define direction of 0C2
	SET_BIT(DDRD, PD7);
	// Choose timer mode as FPWM
	SET_BIT(TCCR2, WGM00);
	SET_BIT(TCCR2, WGM01);
}

void PWM_Start(PWM_PRESCALER prescaler)
{
	switch(prescaler)
	{
		case PWM_No_Prescaling:
		SET_BIT(TCCR2, CS00);
		CLR_BIT(TCCR2, CS01);
		CLR_BIT(TCCR2, CS02);
		break;
		case PWM_8:
		CLR_BIT(TCCR2, CS00);
		SET_BIT(TCCR2, CS01);
		CLR_BIT(TCCR2, CS02);
		break;
		case PWM_64:
		SET_BIT(TCCR2, CS00);
		SET_BIT(TCCR2, CS01);
		CLR_BIT(TCCR2, CS02);
		break;
		case PWM_256:
		CLR_BIT(TCCR2, CS00);
		CLR_BIT(TCCR2, CS01);
		SET_BIT(TCCR2, CS02);
		break;
		case PWM_1024:
		SET_BIT(TCCR2, CS00);
		CLR_BIT(TCCR2, CS01);
		SET_BIT(TCCR2, CS02);
	}
}

void PWM_Stop(void)
{
	// Choose prescaler 0
	CLR_BIT(TCCR2, CS00);
	CLR_BIT(TCCR2, CS01);
	CLR_BIT(TCCR2, CS02);
}

void PWM_SetDuty(PWM_MODE mode, uint8_t dutyCycle)
{
	// Choose mode from table 40
	switch(mode)
	{
		case Disconnected:
		CLR_BIT(TCCR2, COM00);
		CLR_BIT(TCCR2, COM01);
		OCR2 = 0;
		break;
		case Inverting:
		SET_BIT(TCCR2, COM00);
		SET_BIT(TCCR2, COM01);
		OCR2 = (BITS - 1) - ((BITS * dutyCycle) / 100) - 1;
		break;
		case Non_Inverting:
		CLR_BIT(TCCR2, COM00);
		SET_BIT(TCCR2, COM01);
		OCR2 = ((BITS * dutyCycle) / 100) - 1;
	}
	
}