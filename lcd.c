#include "main.h"

void lcd_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LCD_RS|LCD_RW|LCD_EN|LCD_D4|LCD_D5|LCD_D6|LCD_D7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void lcd_send_nibble(uint16_t rs_flag, uint8_t data)
{
	uint16_t data_t = data << 8;
	if(rs_flag == LCD_CMD)
	{
		GPIO_WriteBit(GPIOB, LCD_RS, Bit_RESET);
		data_t = data_t & ~BV(9);
	}
	else
	{
		GPIO_WriteBit(GPIOB, LCD_RS, Bit_SET);
		data_t = data_t | BV(9);
	}
	GPIO_WriteBit(GPIOB, LCD_RW, Bit_RESET);
	GPIO_WriteBit(GPIOB, LCD_D4|LCD_D5|LCD_D6|LCD_D7, Bit_RESET);
	GPIO_Write(GPIOB, data_t);
	GPIO_WriteBit(GPIOB, LCD_EN, Bit_SET);
	delay(2);
	GPIO_WriteBit(GPIOB, LCD_EN, Bit_RESET);
}


void lcd_send_byte(uint16_t rs_flag, uint8_t data)
{
	uint8_t high = data & 0xF0;
	uint8_t low = data << 4;
	
	lcd_send_nibble(rs_flag, high);
	lcd_send_nibble(rs_flag, low);
}


void lcd_init(void)
{
	lcd_gpio_init();
	delay(100);
	lcd_send_byte(LCD_CMD, 0x02);						//Go to start
	lcd_send_byte(LCD_CMD, 0x28);						//font size, no of lines, 4/8 bit
	lcd_send_byte(LCD_CMD, 0x0C);						//display, cursor, blinking
	lcd_send_byte(LCD_CMD, 0x06);						//increment, shift
	lcd_send_byte(LCD_CMD, 0x01);						//CLEAR_BIT screen
	lcd_send_byte(LCD_CMD, LCD_LINE1);
}


void lcd_puts(char *str)
{
	int i;
	for(i=0; str[i] != '\0'; i++)
		lcd_send_byte(LCD_DATA, str[i]);
}

void delay(int time)
{
	int i;
	while(time > 0)
	{
		time--;
		i=500;
		while(i>0)
		{
			i--;
		}
	}
}
