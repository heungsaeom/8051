#include<reg51.h>
#include<string.h>
void main()
{
	char s[]="APPLE IS SWEET ";
	int i,c=0;
	i=strlen(s);
	TMOD=0x20;
	TH1=-6;
	SCON=0x50;
	TR1=1;
	while(1)
	{
	c=0;
	while(c!=i)
	{
		SBUF=s[c];
		while(TI==0);
		TI=0;
		c++;
	}
	}
}