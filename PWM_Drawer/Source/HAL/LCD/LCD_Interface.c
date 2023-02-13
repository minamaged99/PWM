#include "LCD_Private.h"

void LCD_Init()
{
	SET_BIT(LCD_DDR, LCD_D4);
	SET_BIT(LCD_DDR, LCD_D5);
	SET_BIT(LCD_DDR, LCD_D6);
	SET_BIT(LCD_DDR, LCD_D7);
	
	SET_BIT(LCD_CTRL_DDR, LCD_Rs);
	SET_BIT(LCD_CTRL_DDR, LCD_Rw);
	SET_BIT(LCD_CTRL_DDR, LCD_E);
	
	// init in 4-bit mode
	LCD_Write_Command(0x33);
	LCD_Write_Command(0x32);
	LCD_Write_Command(0x28);
	
	LCD_Write_Command(0x01); // clear screen
	LCD_Write_Command(0x02); // return home
	LCD_Write_Command(0x06); // increment cursor to right
	LCD_Write_Command(0x0C); // display on, cursor off
}

void LCD_Write_Command(uint8_t command)
{
	// select command register
	CLR_BIT(LCD_CTRL_PRT, LCD_Rs);
	// select write on screen
	CLR_BIT(LCD_CTRL_PRT, LCD_Rw);
	// ensure that enable is low
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	
	// send the high nibble
	LCD = (command & 0xF0);
	SET_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(1); // One pulse to write data on controller
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	
	// send the low nibble
	LCD = (command & 0x0F) << 4; // shift left so it's on pins 4 5 6 7
	SET_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(1); // One pulse to write data on controller
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(2); // ?
}

void LCD_Write_Character(uint8_t character)
{
	// select data register
	SET_BIT(LCD_CTRL_PRT, LCD_Rs);
	// select write on screen
	CLR_BIT(LCD_CTRL_PRT, LCD_Rw);
	// ensure that enable is low
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	
	// send the high nibble
	LCD = (character & 0xF0);
	SET_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(1); // One pulse to write data on controller
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	
	// send the low nibble
	LCD = (character & 0x0F) << 4; // shift left so it's on pins 4 5 6 7
	SET_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(1); // One pulse to write data on controller
	CLR_BIT(LCD_CTRL_PRT, LCD_E);
	_delay_ms(2);
}

void LCD_Write_String(uint8_t* str)
{
	while (*str != '\0')
	{
		LCD_Write_Character(*str);
		_delay_ms(5);
		str++;
	}
}

void LCD_Write_Number(uint32_t number)
{
	uint8_t* num;
	while (number > 999)
	{
		// Don't show over 3 digits to preserve LCD space.
		number -= 1000;
	}
	if (number > 99)
	{
		ltoa(number / 100, (uint8_t*)num, 10); // Convert number to ascii string so we can print as string
		LCD_Write_String(num);
		number = number - (number / 100) * 100;
	}
	if (number > 9)
	{
		ltoa(number / 10, (uint8_t*)num, 10); // Convert number to ascii string so we can print as string
		LCD_Write_String(num);
		number = number - (number / 10) * 10;
	}
	ltoa(number, (uint8_t*)num, 10); // Convert number to ascii string so we can print as string
	LCD_Write_String(num);
}

void LCD_Clear()
{
	LCD_Write_Command(0x01);
}