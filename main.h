#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stm32l1xx.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_adc.h>

#define BV(x)						1<<x


#define LCD_RS					GPIO_Pin_9
#define LCD_RW					GPIO_Pin_8
#define LCD_EN					GPIO_Pin_5
#define LCD_D4					GPIO_Pin_12
#define LCD_D5					GPIO_Pin_13
#define LCD_D6					GPIO_Pin_14
#define LCD_D7					GPIO_Pin_15

#define LCD_CMD					0				//RS=0 for command mode
#define LCD_DATA				1				//RS=1 for data mode

#define LCD_LINE1				0x80
#define LCD_LINE2				0xC0

	

void lcd_send_byte(uint16_t rs_flag, uint8_t data);
void lcd_puts(char *str);
void lcd_init(void);
void delay(int time);

#endif
