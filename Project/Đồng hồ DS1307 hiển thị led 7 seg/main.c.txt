
#include <REGX51.H> //Thu vien 8051
/***************Dia chi giao tiep DS1307*********************/
#define DS1307_SEC    		0x00 //Giay
#define DS1307_MIN		    0x01 //Phut
#define DS1307_HOUR         0x02 //Gio
#define DS1307_DAY          0x03 //Thu
#define DS1307_DATE         0x04 //Ngay
#define DS1307_MONTH        0x05 //Thang
#define DS1307_YEAR         0x06 //Nam
/****************Ket noi voi DS1307***************************/
#define SCL   	P0_3
#define SDA		P0_2
#define SOUT	P0_4
/****************Nut nhan chinh ngay gio***********************/
#define MODE	P3_4
#define UP		P3_5
#define DOWN	P3_6
#define SAVE	P3_7
/****************LED nhay theo giay***************************/
#define LED		P0_6
/********************DATA OUT 7seg**************************/
#define DOUT	P2
/***************Cac chan quet 12 LED 7 doan*******************/
#define D1_8   	P1		  //Quet hang chuc va don vi: ngay, thang, nam, gio
#define D9		P3_0	  //Quet so phut hang chuc
#define D10		P3_1	  //Quet so phut hang don vi
#define D11		P3_2	  //Quet so giay hang chuc
#define D12		P3_3	  //Quet so giay hang don vi
/****************Khai bao bien va mang du lieu***************************/
unsigned char Mang[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//Mang LED 7
unsigned char SoGioHangChuc,SoGioHangDonVi,SoPhutHangChuc,SoPhutHangDonVi,SoGiayHangChuc,SoGiayHangDonVi;
unsigned char SoNgayHangChuc,SoNgayHangDonVi,SoThangHangChuc,SoThangHangDonVi,SoNamHangChuc,SoNamHangDonVi;
unsigned int time_4,time_5;
char sec,hour,min,day,month,year;
unsigned char KT_MODE=0,time_3,OK=0,so;
/****************Ctr tao tre***************************/
void delay_ms(unsigned int ms)			   
{
 	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<80;j++);
}
/****************Ctr giao tiep IC DS1307***************************/
void I2C_time_5art()	 //ham khoi dong I2C
{
	SCL = 1;		 
	SDA = 1;
	
	SDA = 0; 
	SCL = 0;
	 
}
void I2C_time_5op()	  
{
	SCL = 1; 
	SDA = 0;
	  
	SDA=1;
	SCL=1;
	
}
unsigned char I2C_write(unsigned char dat)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		SDA = (dat & 0x80); ///? 1:0;
		SCL=1;
		SCL=0;
		dat<<=1;
	}
	SCL = 1; 
	SCL = 0;
	return dat;
}
unsigned char I2C_read(void)
{
	bit rd_bit;
	unsigned char i, dat;
	dat = 0x00;
	for(i=0;i<8;i++) 		/* For loop read data 1 byte */
	{
		SCL = 1;
		rd_bit = SDA; 		/* Keep for check acknowledge */
		dat = dat<<1;
		dat = dat | rd_bit; /* Keep bit data in dat */
		SCL = 0; 			/* Clear SCL */
	}
	return dat;
}
// CAC CHUONG TRINH CON CHO DS1307
//******************************************************************************

void DS1307_Write(unsigned char addr,unsigned char dat)
{
	unsigned int temp;
	//********************************************** 
	temp = dat ; 						/*HEX to BCD*/
	dat = (((dat/10)*16)|(temp %10)); 	/*for Led 7seg*/
	//**********************************************
	I2C_time_5art(); 		/* time_5art i2c bus */
	I2C_write(0XD0); 	/* Connect to DS1307 */
	I2C_write(addr); 	/* Requetime_5 RAM address on DS1307 */
	I2C_write(dat); 	/* Connect to DS1307 for Read */
	I2C_time_5op();
}
unsigned char DS1307_Read(unsigned char addr)
{
	unsigned int tm,ret;
	I2C_time_5art(); 		/* time_5art i2c bus */
	I2C_write(0xD0); 	/* Connect to DS1307 */
	I2C_write(addr); 	/* Requetime_5 RAM address on DS1307 */
	I2C_time_5art(); 		/* time_5art i2c bus */
	I2C_write(0XD1); 	/* Connect to DS1307 for Read */
	ret = I2C_read(); 	/* Receive data */
	I2C_time_5op();
	//**********************************************************
	tm = ret; 							/*BCD to HEX*/
	ret = (((ret/16)*10)+ (tm & 0x0f)); 	/*for Led 7seg*/
	//********************************************************** 
	return ret;
}
void DS1307_Set(){
	//Ghi du lieu ngay gio vao DS1307
	DS1307_Write(DS1307_SEC,sec);
	DS1307_Write(DS1307_MIN,min);	    
	DS1307_Write(DS1307_HOUR,hour);       
	DS1307_Write(DS1307_DATE,day);    
	DS1307_Write(DS1307_MONTH,month);  
	DS1307_Write(DS1307_YEAR,year); 
}
void DS1307_GetTime(){
	//Doc du lieu gio tu DS1307
	hour=DS1307_Read(DS1307_HOUR);
	min=DS1307_Read(DS1307_MIN);
	sec=DS1307_Read(DS1307_SEC);
}
void DS1307_GetDate(){
	//Doc du lieu ngay tu DS1307
	day=DS1307_Read(DS1307_DATE);
	month=DS1307_Read(DS1307_MONTH);
	year=DS1307_Read(DS1307_YEAR);
}//End code DS1307
/****************Ctr quet 12 LED 7 doan ***************************/
void Display(){//Ham hien thi ngay, thang, nam, gio, phut, giay 
	D1_8=0xfe;
	DOUT=Mang[SoNgayHangChuc];
	delay_ms(1);DOUT=0xff;
	D1_8=0xfd;
	DOUT=Mang[SoNgayHangDonVi];
	delay_ms(1);DOUT=0xff;
	D1_8=0xfb;
	DOUT=Mang[SoThangHangChuc];
	delay_ms(1);DOUT=0xff;
	D1_8=0xf7;
	DOUT=Mang[SoThangHangDonVi];
	delay_ms(1);DOUT=0xff;
	D1_8=0xef; 
	DOUT=Mang[SoNamHangChuc];
	delay_ms(1);DOUT=0xff;
	D1_8=0xdf;
	DOUT=Mang[SoNamHangDonVi];
	delay_ms(1);DOUT=0xff;
	D1_8=0xbf;
	DOUT=Mang[SoGioHangChuc];
	delay_ms(1);DOUT=0xff;
	D1_8=0x7f;
	DOUT=Mang[SoGioHangDonVi];
	delay_ms(1);DOUT=0xff;
	D1_8=0xff;D9=0;
	DOUT=Mang[SoPhutHangChuc];
	delay_ms(1);DOUT=0xff;
	D9=1;D10=0;
	DOUT=Mang[SoPhutHangDonVi];
	delay_ms(1);DOUT=0xff;
	D10=1;D11=0; 
	DOUT=Mang[SoGiayHangChuc];
	delay_ms(1);DOUT=0xff;
	D11=1;D12=0;
	DOUT=Mang[SoGiayHangDonVi];
	delay_ms(1);DOUT=0xff;
	D12=1;
}
void Setting(){//Ham hien thi qua trinh chinh ngay gio
	if(KT_MODE==4 && time_5<100){
		D1_8=0xfe;
		DOUT=0xff;
		delay_ms(1);
		D1_8=0xfd;
		DOUT=0xff;
		delay_ms(1);	
	}else{ 
		D1_8=0xfe;
		DOUT=Mang[SoNgayHangChuc];
		delay_ms(1);DOUT=0xff;
		D1_8=0xfd;
		DOUT=Mang[SoNgayHangDonVi];
		delay_ms(1);DOUT=0xff;
		if(time_5>200) time_5=0;
	}
	if(KT_MODE==5 && time_5<100){
		D1_8=0xfb;
		DOUT=0xff;
		delay_ms(1);
		D1_8=0xf7;
		DOUT=0xff;
		delay_ms(1);	
	}else{ 
		D1_8=0xfb;
		DOUT=Mang[SoThangHangChuc];
		delay_ms(1);DOUT=0xff;
		D1_8=0xf7;
		DOUT=Mang[SoThangHangDonVi];
		delay_ms(1);DOUT=0xff;
		if(time_5>200) time_5=0;
	}
	if(KT_MODE==6 && time_5<100){
		D1_8=0xef;
		DOUT=0xff;
		delay_ms(1);
		D1_8=0xdf;
		DOUT=0xff;
		delay_ms(1);	
	}else{ 
		D1_8=0xef; 
		DOUT=Mang[SoNamHangChuc];
		delay_ms(1);DOUT=0xff;
		D1_8=0xdf;
		DOUT=Mang[SoNamHangDonVi];
		delay_ms(1);DOUT=0xff;
	}
	if(KT_MODE==1 && time_5<100){
		D1_8=0xbf;
		DOUT=0xff;
		delay_ms(1);
		D1_8=0x7f;
		DOUT=0xff;
		delay_ms(1);	
	}else{ 
		D1_8=0xbf; 
		DOUT=Mang[SoGioHangChuc];
		delay_ms(1);DOUT=0xff;
		D1_8=0x7f;
		DOUT=Mang[SoGioHangDonVi];
		delay_ms(1);DOUT=0xff;
	}	
	if(KT_MODE==2 && time_5<100){
		D1_8=0xff;D9=0;
		DOUT=0xff;
		delay_ms(1);
		D9=1;D10=0;
		DOUT=0xff;
		delay_ms(1);	
	}else{ 
		D1_8=0xff;D9=0; 
		DOUT=Mang[SoPhutHangChuc];
		delay_ms(1);DOUT=0xff;
		D9=1;D10=0;
		DOUT=Mang[SoPhutHangDonVi];
		delay_ms(1);DOUT=0xff;
	}
	if(KT_MODE==3 && time_5<100){
		D10=1;D11=0;
		DOUT=0xff;
		delay_ms(1);
		D11=1;D12=0;
		DOUT=0xff;
		delay_ms(1);
		D12=1;
		delay_ms(1);	
	}else{ 
		D10=1;D11=0; 
		DOUT=Mang[SoGiayHangChuc];
		delay_ms(1);DOUT=0xff;
		D11=1;D12=0;
		DOUT=Mang[SoGiayHangDonVi];
		delay_ms(1);DOUT=0xff;
		D12=1;
		delay_ms(1);
	}
	if(time_5>300){ time_5=0;}
}

/****************Ctr chuyen doi so sang LED 7 doan***************************/
void Convert_Number(){
	SoNgayHangChuc=day/10;
	SoNgayHangDonVi=day%10;
	SoThangHangChuc=month/10;
	SoThangHangDonVi=month%10;
	SoNamHangChuc=year/10;
	SoNamHangDonVi=year%10;
	SoGiayHangChuc=sec/10;
	SoGiayHangDonVi=sec%10;
	SoPhutHangChuc=min/10;
	SoPhutHangDonVi=min%10;
	SoGioHangChuc=hour/10;
	SoGioHangDonVi=hour%10;
}

/****************Ctr phim nhan chinh ngay gio***************************/
void ScanKey(){
	if(!MODE){
		LED=0;
	 	delay_ms(50);
		KT_MODE++;
		time_5=0; 	
		if(KT_MODE>6)KT_MODE=1;
		time_4=0;
		while(!MODE);	
		OK=1;
	}
	if(!SAVE && OK){	
		delay_ms(20);
		if(KT_MODE){
			DS1307_Set(); 
			DS1307_GetDate();
		}
		KT_MODE=0;
		OK=0;
		time_4=0;
	}
	if(time_4>30000 && KT_MODE){	
		DS1307_GetDate();
		KT_MODE=0;
		OK=0;
		time_4=0;
	}
	if(KT_MODE)
	{
		switch(KT_MODE)
		{
		 	case 4:    //chinh ngay
			{
				if(!DOWN)
				{
				 	delay_ms(20);
					day--;
					if(day<1)
						day=31;	time_4=0;
					while(!DOWN);
				}
				else if(!UP)
				{
				 	delay_ms(20);
					day++;
					if(day>31)
						day=1;time_4=0;
					while(!UP);
				}	
			}
			break;
			case 5:	  //chinh thang
			{ 				
				if(!DOWN)
				{
				 	delay_ms(20);
					month--;
					if(month<1)
						month=12;time_4=0;
					while(!DOWN);
				}
				else if(!UP)
				{
				 	delay_ms(20);
					month++;
					if(month>12)
						month=1;time_4=0;
					while(!UP);
				}
			}
			break;
			case 6:	 //chinh nam
			{ 
			
				if(!DOWN)
				{
				 	delay_ms(20);
					year--;
					if(year<0)
						year=99;
					while(!DOWN);time_4=0;
				}
				else if(!UP)
				{
				 	delay_ms(20);
					year++;
					if(year>99)
						year=0;
					while(!UP);time_4=0;
				}	
			}
			break;
		
			case 1:	   //chinh gio
			{ 
			
				if(!DOWN)
				{
				 	delay_ms(20);
					hour--;
					if(hour<0) hour=23;
					time_4=0;
					while(!DOWN);
				}
				else if(!UP)
				{
				 	delay_ms(20);
					hour++;
					if(hour>23)
						hour=0;time_4=0;
					while(!UP);
				}
			}
			break;	 //chinh phut
			case 2:
			{ 
				if(!DOWN)
				{
				 	delay_ms(20);
					min--;
					if(min<0)
						min=59;time_4=0;
					while(!DOWN);
				}
				else if(!UP)
				{
				 	delay_ms(20);
					min++;
					if(min>59)
						min=0;time_4=0;
					while(!UP);
				} 
			}
			break;
			case 3:	 //chinh giay
			{ 
				if(!DOWN)
				{
				 	delay_ms(20);
					sec--;
					if(sec<0)
						sec=59;	 time_4=0;
					while(!DOWN);
				}
				else if(!UP)
				{
				 	delay_ms(20);
					sec++;
					if(sec>59)
						sec=0;	time_4=0;
					while(!UP);
				}
			}
			break;
		}
		Setting();
	}
}
/****************Ctr ngat timer0***************************/
void INT_timer(void) interrupt 1 {    
	TF0 = 0;//Xoa co tran
	TH0 =0xe5;//nap lai gia tri
	TL0 =0xf8;
	//Cac bien dem
	//time_0++;
	//time_1++;
	time_3++;
	time_4++;
	time_5++;
} 
/****************Ctr chinh***************************/
void main(){
	LED=0;
	DS1307_Write(7,10);//Tao xung 1Hz tu chan SOUT
	for(time_4=211;time_4>0;time_4--){//Quet led luc khoi dong
		if(time_4==210) DOUT=0xfe;
		else if(time_4==180) DOUT=0xfd;
		else if(time_4==150) DOUT=0xfb;
		else if(time_4==120) DOUT=0xf7;
		else if(time_4==90) DOUT=0xef;
		else if(time_4==60) DOUT=0xdf;
		else if(time_4==30) DOUT=0xbf;
		D1_8=0xfe;delay_ms(1);D1_8=0xfd;delay_ms(1);D1_8=0xfb;delay_ms(1);D1_8=0xf7;delay_ms(1);
		D1_8=0xef; delay_ms(1);D1_8=0xdf;delay_ms(1);D1_8=0xbf;delay_ms(1);D1_8=0x7f;delay_ms(1);
		D1_8=0xff;D9=0;delay_ms(1);D9=1;D10=0;delay_ms(1);D10=1;D11=0;delay_ms(1);D11=1;D12=0;delay_ms(1);D12=1;
	}
	if(SAVE==0){//Giu phim nay de reset lai ngay gio khi khoi dong
		sec=0;min=0;hour=12;day=1;month=1;year=15;
		DS1307_Set();
	}
	TR0=1; //chay timer 0
	ET0=1; //ngat timer 0 
	EA=1; //cho phep ngat
	DS1307_GetTime(); //Lay gio
	DS1307_GetDate(); //lay ngay
	LED=1;
    while(1){
		ScanKey();//Quet nut nhan
		if(time_3>100){	
			Convert_Number();//Chuyen doi so sang LED 7
			time_3=0;
		}
		if(!KT_MODE){
			if(SOUT)so=1;
			if(!SOUT && so){
			   sec=DS1307_Read(DS1307_SEC);
			   if(sec==0)DS1307_GetTime();
			   so=0;
			}
			if(hour==0 && min==0 && sec==0)DS1307_GetDate();//Lay du lieu ngay moi
			LED=SOUT;	 //LED giay nhap nhay chuan 1hz
			Display();//hien thi ngay gio
		}else LED=0;	
    }
}
/******************* THE END ***************************/