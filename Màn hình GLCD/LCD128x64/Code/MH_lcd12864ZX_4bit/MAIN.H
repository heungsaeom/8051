#ifndef __MAIN_
#define __MAIN_

#include <regx52.h>
#include <DELAY\delay.h>
#include <GLCD\glcd.h>

/* =================CONFIGURATION======================= */
// PORT0 --------------------------------------------------
sbit LCD_RS=P0^0;
sbit LCD_RW=P0^1;
sbit LCD_E=P0^2;
sbit LCD_PSB =P0^3;		
sbit LCD_RST =P0^5;

// PORT1 --------------------------------------------------	
// PORT2 --------------------------------------------------
sbit LCD_D4=P2^4;
sbit LCD_D5=P2^5;
sbit LCD_D6=P2^6;
sbit LCD_D7 =P2^7;		
#define Busy    0x80 

// PORT3 --------------------------------------------------

#endif