#ifndef __GLCD_
#define __GLCD_

#include <main.h>

void lcd_send_4bit_data ( unsigned char cX );
void lcd_send_command (unsigned char cX );
void write_data_lcd(unsigned char WDLCD);
void write_command_lcd(unsigned char WCLCD,unsigned char BuysC);
//unsigned char read_data_lcd(void);
//unsigned char read_status_lcd(void);
void lcd_init(void);
void lcd_clear(void);
void lcd_flash(void);
void lcd_putchar(unsigned char X, unsigned char Y, unsigned char DData);
void lcd_puts(unsigned char X, unsigned char Y, unsigned char *DData);
void lcd_display_image (unsigned char *DData);

#endif