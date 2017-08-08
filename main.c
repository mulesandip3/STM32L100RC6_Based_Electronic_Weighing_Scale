#include "main.h"
#include "hx711.h"

unsigned long count_t;
double weight;
char str[20];
char *name = "Weighing Scale";
char *str_1 = "kg";

int main()
{
	hx711_init();
	set_gain(128);
	lcd_init();
	while(1)
  {
		lcd_send_byte(LCD_CMD, 0x01);
	  lcd_send_byte(LCD_CMD, LCD_LINE1);
    lcd_puts(name);
	  count_t = read();
    weight = (((4.555e-5)*count_t) - 347.8)-7;
	  sprintf(str,"count=%.4g",weight);
		lcd_send_byte(LCD_CMD, LCD_LINE2);
		lcd_puts(str);
		lcd_send_byte(LCD_CMD, LCD_LINE2);
		lcd_send_byte(LCD_CMD, 0xCD);
		lcd_puts(str_1);
		delay(1000);
	}

}

