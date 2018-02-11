#include<reg51.h>
sbit pin=P1^5;
void delay(void);

void main()
{
	unsigned int i;
	pin=0;
	TMOD=0x10;
	while(1)
	{
		for(i=0;i<400;i++)
		 delay();
		pin=~pin;
		for(i=0;i<400;i++)
		 delay();
	}
}

void delay(void)
{
	TH1=0xEE;
	TL1=0x00;
	TR1=1;
	while(TF1==0);
	TR1=0;
	TF1=0;
}