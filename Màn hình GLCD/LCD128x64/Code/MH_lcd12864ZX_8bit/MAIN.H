/*******************************************************************
  *	@file 		main.h
  * @author  	MinhHaGroup
  * @version 	V1.0.0
  * @date   
  * @brief  	File  cau hinh su dung cho AT89S52
********************************************************************/
#ifndef __MAIN_
#define __MAIN_

#include <regx52.h>
#include <DELAY\delay.h>
#include <GLCD\glcd.h>

/* =================CONFIGURATION======================= */
// --------------------------------------------------------
// PORT0 --------------------------------------------------
sbit LCD_RS=P0^0;
sbit LCD_RW=P0^1;
sbit LCD_E=P0^2;
sbit LCD_PSB =P0^3;		
sbit LCD_RST =P0^5;

// PORT1 --------------------------------------------------
// PORT2 --------------------------------------------------
#define LCD_Data P2
#define Busy    0x80 

// PORT3 --------------------------------------------------

#endif
/* -----------------END OF FILE--------------------------- */