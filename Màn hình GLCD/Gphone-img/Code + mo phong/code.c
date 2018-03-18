#include<regx52.h>
#include <INTRINS.H>
// Thu vien LCD
#define CLK    P2_7
#define DC     P2_6
#define DATA   P2_5
#define SCE    P2_4 

#define DDROUT 1
#define DDRIN  0
#define CMD    0
#define DAT    1
				  
/*-----------------------------------------*/
void delay_ms(unsigned int t)  
{
unsigned int x,y;
for(x=0;x<t;x++)
{
for(y=0;y<123;y++);
}	
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//	
unsigned char code font_img[8][128] =
{ 


};	 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// 

void SPI_truyen(unsigned char cd,unsigned char myData)
{
unsigned char i;
DC= cd;
for(i=0;i<8;i++){
                DATA=(myData & 0x80) ;
                CLK=1;
                myData<<=1;
                CLK=0;
                }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void LCD_chonvitri(unsigned char x, unsigned char y, unsigned char giatri)
{
	x=x*giatri; 
    SPI_truyen(CMD,(x & 0x0f));
    SPI_truyen(CMD,((x >> 4)|0x10));
    SPI_truyen(CMD,((y & 0x0f)|0xb0));
} 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// 
void LCD_xoamanhinh() 
{
    unsigned char u,w;
    for(u=0;u<8;u++){
        LCD_chonvitri(0,u,1);
        for(w=0;w<130;w++)
            SPI_truyen(DAT,0x00);
    }
    LCD_chonvitri(0,0,1);
} 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// 
 
void LCD_khoitao() 
{
    CLK=0;
    delay_ms(2); 
    SCE=0;
    SPI_truyen(CMD,0xE2); 
    delay_ms(10);
    SPI_truyen(CMD,0x2C);
    SPI_truyen(CMD,0x2E);
    SPI_truyen(CMD,0x2F); 
    SPI_truyen(CMD,0xAF); 
    LCD_xoamanhinh();  
    SPI_truyen(CMD,0xA6);
	  //SPI_truyen(CMD,0xA1); // dung trong mo phong. mach that xoa dong nay
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void img() 
{
	unsigned char v;
	unsigned char x;

    for(x=0;x<8;x++)					   
	{
	    LCD_chonvitri(0,x,0);
		for(v=0;v<128;v++)
		  {
			SPI_truyen(DAT,font_img[x][v]);
		  }
	}
}

void main()						 
{										    
  LCD_khoitao();
  img();
  while(1)
  {
   
  }
}
