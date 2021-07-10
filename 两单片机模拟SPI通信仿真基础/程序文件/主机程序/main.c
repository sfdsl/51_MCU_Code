#include <reg51.h>
#include <STDIO.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int  u16;
	
sbit CLK =P1^0;    //时钟信号
sbit MOSI=P1^1;    //主发从接
sbit MISO=P1^2;    //主接从发
sbit SS  =P1^3;    //片选（使能）信号

void Delay_ms(unsigned int ms)		//@12.000MHz
{
	unsigned char i, j;
  for(;ms>1;ms--)
	{
			i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}


void Master_Send_Dat(u8 dat) //发送数据程序
{
  u8 i;
	SS=0;//主机选择从机
	for(i=0;i<8;i++)
	{
		 if(dat&0x80)
			MOSI=1;
		 else
		  MOSI=0;
	    dat=(dat<<1);
		 
		  CLK=1;
			_nop_();
			_nop_();
		 	CLK=0;
		 _nop_();
		 _nop_();
	}
	SS=1;
	Delay_ms(1);
}

u8 Mater_Receive_Dat(void)
{
  u8 i,dat=0;
	SS=0;//主机选择从机
	for(i=0;i<8;i++)
	{
		  dat=dat<<1;
			dat=dat|MISO;
			
			CLK=1;
			_nop_();
			_nop_();
		 	CLK=0;
		 _nop_();
		 _nop_();		
	}
	SS=1;
	return dat;
}


 u8 code num[10]={0x3f,0x06,0x5b,0x4f,0x66,
             0x6d,0x7d,0x07,0x7f,0x6f};
 
void main(void)
{
 u8 exdat=1,i=0;
	CLK=0;
	P2=0X00;
	while(1)
	{
	 for(i=0;i<10;i++)
		{		
				Master_Send_Dat(i);
				Delay_ms(500);
		
				exdat=Mater_Receive_Dat();
				P2=num[exdat];
				Delay_ms(500);
		}
	}
}