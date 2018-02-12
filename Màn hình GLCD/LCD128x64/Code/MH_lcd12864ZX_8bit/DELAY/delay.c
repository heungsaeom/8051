#include <main.h>
void delay_ms(unsigned int Time)
{
	unsigned int i,j,t;
	t=Time;
	for(i=0;i<t;i++)
	{
		for(j=0;j<125;j++);
	}
}
void delay_us(unsigned int Time)
{
	unsigned int i,j;
	for(i=0;i<Time;i++)
	{
		for(j=0;j<2;j++);
	}
} 
