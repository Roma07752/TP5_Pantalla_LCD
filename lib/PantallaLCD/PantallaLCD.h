#ifndef PANTALLALCD_H
#define PANTALLALCD_H

#include "stm32f103xb.h"
#include <stdint.h>

#define LCD_PORT GPIOB

#define RS   0 
#define EN   2 
#define D4   10  
#define D5   11  
#define D6   12  
#define D7   13  

void lcd_init();
void lcd_clear();
void lcd_setCursor(int col, int row);
void lcd_print(char *str);
void lcd_scrollDisplayLeft();
void lcd_scrollDisplayRight();
void lcd_backlight();
void lcd_noBacklight();
void lcd_createChar(char num, char datos[8]);

#endif
