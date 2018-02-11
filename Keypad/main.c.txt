#include<reg51.h>
#define row P2
#define col P3
#define LCD P0
sbit rs = P2^5;
sbit rw = P2^6;
sbit e = P2^7;
unsigned char value;
unsigned char *display;

void msdelay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<1275;j++);
	}
}
void lcdcmd(unsigned char value)
{
		LCD = value;
		rs = 0;
		rw = 0;
		e = 1;
		msdelay(1);
		e=0;
}

void lcddata(unsigned char value)
{
		LCD = value;
		rs = 1;
		rw = 0;
		e = 1;
		msdelay(10);
		e=0;
}


void delay(void)
{
	unsigned int i;
	for(i=0;i<20000;i++);
}


void main()
{
	lcdcmd(0x38);
	msdelay(10);
	lcdcmd(0x0F);
	msdelay(10);	
	lcdcmd(0x80);
	msdelay(10);	
	while(1)
	{
		unsigned char x[4];
		unsigned int i;
		unsigned char temp;
		x[0]=0x0E;
		x[1]=0x0D;
		x[2]=0x0B;
		x[3]=0x07;
		row=0x00;
		col=0xFF;
			while(P3==0xFF);
			for(i=0;i<4;i++)
			{
				row=x[i];
				if(col==0xFE)
				{
					if(x[i]==0x0E)
					{
						temp=0x01;
						lcddata('1');
					}
					else if(x[i]==0x0D)
					{
						temp=0x04;
						
					}
					else if(x[i]==0x0B)
					{
						temp=0x07;
						
					}
					delay();
				}
				else if(col==0xFD)
				{
					if(x[i]==0x0E)
					{
						temp=0x02;
						
					}
					else if(x[i]==0x0D)
					{
						temp=0x05;
						
					}
					else if(x[i]==0x0B)
					{
						temp=0x08;
						
					}
					else if(x[i]==0x07)
					{
						
						
					}
					delay();
				}
				else if(col==0xFB)
				{
					if(x[i]==0x0E)
					{
						temp=0x03;
						
					}
					else if(x[i]==0x0D)
					{
						temp=0x06;
						
					}
					else if(x[i]==0x0B)
					{
						temp=0x09;
						
					}
					delay();
					
				}
			}
			
		
	}
}