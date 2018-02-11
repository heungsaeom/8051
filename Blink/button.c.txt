#include<reg51.h>
sbit led=P1^1;
sbit btn=P2^1;
sbit btn2=P2^2;
void main()
{
	int i;
	while(1)
	{
		if(btn==0)
		{
			for(i=0;i<5000;i++);
			if(btn==0)
			{
				led=~led;
			}
		}
		if(btn2==0)
		{
			for(i=0;i<5000;i++);
			if(btn2==0)
			{
				led=0;
			}
		}
	}
}