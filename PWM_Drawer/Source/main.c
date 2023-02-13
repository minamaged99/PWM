#include "main.h"

void DrawSignal(uint16_t frequency, uint16_t duty_cycle)
{
	LCD_Write_Command(0x80);
	#if FREQ_MODE
		LCD_Write_String("F=");
		LCD_Write_Number(frequency / 1000);
		LCD_Write_String("kHz ");
	#else
		uint16_t period = 1000000 / frequency;
		LCD_Write_String("T=");
		LCD_Write_Number(period);
		LCD_Write_String("us ");
	#endif
	LCD_Write_String("d=");
	LCD_Write_Number(duty_cycle);
	LCD_Write_String("%     ");

	// Draw signal
	LCD_Write_Command(0xC0);
	LCD_Write_String("__");
	for (uint8_t i = 0; i < 3; i++)
	{
		uint16_t temp = duty_cycle;
		for (uint8_t p = 0; p < 4; p++)
		{
			if (temp > 25)
			{
				LCD_Write_Character('-');
				temp -= 25;
			}
			else if (temp > 0)
			{
				LCD_Write_Character('-');
				temp = 0;
			}
			else
			{
				LCD_Write_Character('_');
				temp = 0;
			}
		}
	}
	LCD_Write_String("__");
}

int main(void)
{

	// PWM 
    PWM_Init();
	PWM_Start(PWM_No_Prescaling);	// No prescaling
	PWM_SetDuty(Non_Inverting, 50);

	// ICU 
	uint16_t a, b, c;

	// LCD 
	LCD_Init();
	LCD_Clear();
	LCD_Write_String("Reading");


	while (1)
    {
		// Read Signal
		TCCR1A = 0;
		TCNT1=0;
		TIFR = (1<<ICF1);  	// Clear ICF (Input Capture flag) flag

		TCCR1B = 0x41;  	// Rising edge, no prescaler
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		// Take value of capture register
		TIFR = (1<<ICF1);  	// Clear ICF flag */

		TCCR1B = 0x01;  	// Falling edge, no prescaler
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		// Take value of capture register
		TIFR = (1<<ICF1);  	// Clear ICF flag

		TCCR1B = 0x41;  	// Rising edge, no prescaler
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;  		// Take value of capture register
		TIFR = (1<<ICF1);  	// Clear ICF flag

		TCCR1B = 0;  		// Stop the timer

		if(a < b && b < c)  	// Check for valid condition, to avoid timer overflow reading
		{
			uint16_t period = c - a;

			// Calculate frequency
			uint16_t frequency = F_CPU / period;

			// Calculate duty cycle
			uint16_t duty_cycle = ((b - a) * 100 ) / period;

			DrawSignal(frequency, duty_cycle);
		}
		_delay_ms(50);
	}
}

