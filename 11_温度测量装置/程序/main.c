#include "config.h"
#include "lcd1602.h"
#include "DS18B20.h"
#include "delay.h"
#include "TLC2543.h"
#include "thermocouple.h"

void display_TLC2543_temp(uchar Temp_Start )
{  
	  uchar i=0;
	  float m1=0.0;
	   uint ad_num=0;
     uint tempH=0,tempL=0;
	
	     while(1)
			{
				ad_num=read2543(0);
				m1=(float)(1.221*ad_num-2494);//0.0012219961298302
				 i++;
				tempH=(u16)(100*table[i+1]);
				tempL=(u16)(100*table[i]);
			   if(m1>=tempL && m1<=tempH)
					  break;
			}
			Disp_number(Temp_Start,1,(u16)i,5);
			DisplayOneChar(Temp_Start+5,1,0XDF-0X30);
			DisplayOneChar(Temp_Start+6,1,'C'-0X30);
}

Temperature_value Real_temp;//定义一个温度结构体
 
void display_temperature(uchar Temp_Start)
{
	  uchar  High_T,Low_T;
		//Temperature_value Real_temp;
  	Real_temp=Read18B20_Temperature();
	
		if(Real_temp.tempflag==1)
		{
				DisplayOneChar(Temp_Start,1,'-');
				High_T=Real_temp.tempr/10;
				Low_T=Real_temp.tempr%10;
				DisplayOneChar(Temp_Start+1,1,High_T);
				DisplayOneChar(Temp_Start+2,1,Low_T);
				DisplayOneChar(Temp_Start+3,1,'.');
				DisplayOneChar(Temp_Start+4,1,Real_temp.fraction);
		}else
		{
				High_T=Real_temp.tempr/10;
				Low_T=Real_temp.tempr%10;
				DisplayOneChar(Temp_Start,1,High_T);
				DisplayOneChar(Temp_Start+1,1,Low_T);
				DisplayChars(Temp_Start+2,1,".");
				DisplayOneChar(Temp_Start+3,1,Real_temp.fraction);
		}		
}

/*
温度控制器
一通电，LED显示温度为20摄氏度，然后通过按键
实行加减到指定的温度，然后继电器闭合开始加热，
当加热的温度没有达到指定温度，LED闪烁并发出报警
*/
void main(void)
 { 
	  unsigned char High_Temp=30,state=0;
   // Write your code here
	 LCD_Init();//LCD1602的初始化
   while (1)
   {
		  	DisplayChars(0,0,"ThermTemp:");
				display_TLC2543_temp(0);//显示热电偶采集的温度
   }
}
 
