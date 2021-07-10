#include "MAX6675.h"

float MAX6675_Temper;
float MAX31855_Temper;


void MAX6675_Delay1us()		//@33.1776MHz
{
	unsigned char i;

	i = 9;
	while (--i);
}

void MAX6675_Delay_us(u16 x)
{
	u16 i;
	for(i=0;i<x;i++)
		MAX6675_Delay1us();
}


u16 MAX6675_ReadDat() 
{
  u16 d;
	u8 i; 

  MAX6675_CS=0;
	MAX6675_CLK=0;
  MAX6675_Delay_us(2);
  for(i=0;i<16;i++)
  {
		d<<=1; 
		MAX6675_Delay_us(2);
    MAX6675_CLK=1;
		if(MAX6675_DAT)
     d++;
		 MAX6675_Delay_us(2);
		 MAX6675_CLK=0; 
  }
  MAX6675_CS=1;
  return d;
}

void MAX6675_ReadTemper() 
{
  u16 d;
	
  d=MAX6675_ReadDat();//读取MAX6675当前的温度值
  MAX6675_Temper=((d>>3)&0x0fff)*0.25; 
}


void Max6675_Init()
{
//	GPIO_Init(GPIO3,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_IPU);
	MAX6675_CS=1;
	MAX6675_CLK=1;
	MAX6675_DAT=1;

}

/******************************************************************************************************************/
u32 MAX31855_ReadDat() 
{
  u32 d;
	u8 i;
	 
  MAX6675_CS=0;
	MAX6675_CLK=0;
  MAX6675_Delay_us(12);
  for(i=0;i<32;i++)
  {
		d<<=1; 
		MAX6675_Delay_us(12);
    MAX6675_CLK=1;
		if(MAX6675_DAT)
     d++;
		 MAX6675_Delay_us(12);
		 MAX6675_CLK=0; 
  }
  MAX6675_CS=1;
  return d;
}

void MAX31855_ReadTemper() 
{
  u32 d;
	
  d=MAX31855_ReadDat();//读取MAX6675当前的温度值
  MAX31855_Temper=((d>>18)&0x3fff)*0.25+0.5;  //+0.5四舍五入
}










