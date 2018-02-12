/*******************************************************************
  *	@file 		glcd.c
  * @author  	MinhHaGroup
  * @version 	V1.0.0
  * @date   
  * @brief  	File cac ham de dieu khien LCD 128x64
********************************************************************/
#include "main.h"


void write_data_lcd(unsigned char WDLCD)
{
	delay_us(200);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY 
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_Data = WDLCD;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 0;
}
// ==============================================================================
void write_command_lcd(unsigned char WCLCD,unsigned char BuysC) 
{
	if (BuysC) 
	delay_us(200);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY 
	LCD_RS = 0;
	LCD_RW = 0; 
	LCD_Data = WCLCD;
	LCD_E = 1; 
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 0;  
}
// ==============================================================================
// HAM KHOI TAO LCD ------------------------------------------------
// MODE 8 bit ------------------------------------------------------
void lcd_init(void) 
{
	// Function set
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	delay_us(150);											// delay > 100us
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	delay_us(50);												// delay > 37us
	
	// Display ON/OFF control
	write_command_lcd(0x0C,1); 					// Cho phep hien thi ra LCD 128x64
	delay_us(120);											// delay > 100us
	
	// Clear LCD
	write_command_lcd(0x01,1); 					// Xoa man hinh			
	delay_ms(40);												// delay > 10ms
	
	// Entry mode set
	write_command_lcd(0x06,1); 					// Chon che do hien thi ki tu ra man hinh LCD 128x64 (Ki tu sau xuat hien ben phai ki tu truoc)
}
// ==============================================================================
void lcd_clear(void) 
{
	write_command_lcd(0x01,1);
	//write_command_lcd(0x34,1); 
	write_command_lcd(0x30,1); 
}
// ==============================================================================
void lcd_flash(void)	
{
	write_command_lcd(0x08,1);
	delay_ms(400);
	write_command_lcd(0x0c,1); 
	delay_ms(400);
	write_command_lcd(0x08,1); 
	delay_ms(400);
	write_command_lcd(0x0c,1); 
	delay_ms(400);
	write_command_lcd(0x08,1); 
	delay_ms(400);
}
// ==============================================================================
void lcd_putchar(unsigned char X, unsigned char Y, unsigned char DData)
{
	if(Y<1)
		Y=1;
	if(Y>4)
		Y=4;
	X &= 0x0F; 
	switch(Y)
	{
		case 1:X|=0X80;break;
		case 2:X|=0X90;break;
		case 3:X|=0X88;break;
		case 4:X|=0X98;break;
	}
	write_command_lcd(X, 0); 
	write_data_lcd(DData);
}
// ==============================================================================
void lcd_puts(unsigned char X, unsigned char Y, unsigned char *DData)
{
	unsigned char ListLength,X2;

	ListLength = 0;
	X2=X;
	if(Y<1)
		Y=1;
	if(Y>4)
		Y=4;
	X &= 0x0F; 
	switch(Y)
	{
		case 1:X2|=0X80;break;	
		case 2:X2|=0X90;break;
		case 3:X2|=0X88;break;
		case 4:X2|=0X98;break;
	}
	write_command_lcd(X2, 1); 
	while (DData[ListLength]>=0x20) 
	{
		if (X <= 0x0F) 
		{
			write_data_lcd(DData[ListLength]);
			ListLength++;
			X++;
			delay_ms(5);
		}
	}
}
// ==============================================================================
void lcd_display_image  (unsigned char *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)
	{		
		for(x=0;x<32;x++)
		{				
			write_command_lcd(0x34,1);
			write_command_lcd((0x80+x),1);
			write_command_lcd((0x80+i),1);	
			write_command_lcd(0x30,1);		
			for(y=0;y<16;y++)	
				write_data_lcd(DData[tmp+y]);
			tmp+=16;		
		}
		i+=8;
	}
		write_command_lcd(0x36,1);	
		write_command_lcd(0x30,1);
}
// ==============================================================================
/**
unsigned char read_data_lcd(void)
{
	LCD_RS = 1; 
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
	return(LCD_Data);
}
**

unsigned char read_status_lcd (void)
{
	write_data_port(0xFF); 
	LCD_RS = 0;
	LCD_RW = 1; 
	LCD_E = 1;
	while (LCD_Data & BUSY); 
	LCD_E = 0;
	return(LCD_Data);
}*/
// ==============================================================================
/* -----------------END OF FILE---------------------------- */

