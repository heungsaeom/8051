#include <main.h>

void main()
{
	delay_ms(400);				// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY (>40ms)
	lcd_init();
	delay_ms(5);
	LCD_RST=1;
	lcd_clear();
	lcd_putchar(1,1,'A');
	while(1)
	{
		/*lcd_puts(1,1,"WELLCOME TO!");
		lcd_puts(1,2,"MINHHAGROUP ");
		lcd_puts(0,3," 11/N66-DCV-HBT");
		lcd_puts(0,4,"8051/AVR/PIC/ARM");
		//delay_ms(100);*/
	}
}