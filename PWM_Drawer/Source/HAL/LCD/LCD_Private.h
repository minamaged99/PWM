#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_


#include "LCD_Config.h"

void LCD_Init();

void LCD_Write_Command(uint8_t command);
void LCD_Write_Character(uint8_t character);
void LCD_Write_String(uint8_t* str);
void LCD_Write_Number(uint32_t number);
void LCD_Clear();


#endif /* LED0_PRIVATE_H_ */