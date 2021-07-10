#include <reg51.h>
#include <STDIO.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int  u16;

sbit CLK =P1^0;
sbit MOSI=P1^1;
sbit MISO=P1^2;
sbit SS  =P1^3;

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

u8 Slave_Receive_Dat(void)
{
  u8 i,dat=0;
	while(SS);//�ȴ�ss����
	for(i=0;i<8;i++)
	{
	 while(CLK==0);//�ȴ�CLK����
   while(CLK==1);//�ȴ�CLK����
		dat=dat<<1;
		dat=dat|MOSI;
	}
	while(SS==0);//�ȴ�ss����
	return dat;
}

void Slave_Send_Dat(u8 dat) //�������ݳ���
{
  u8 i;
	while(SS);//�ȴ�ss����
	for(i=0;i<8;i++)
	{
	  while(CLK==0);//�ȴ�CLK����
		while(CLK==1);//�ȴ�CLK����
		  dat=(dat<<1); 
		  if(dat&0x80)
			MISO=1;
		 else
		  MISO=0;
	}
	while(SS==0);//�ȴ�ss����
}

 u8 code num[10]={0x3f,0x06,0x5b,0x4f,0x66,
             0x6d,0x7d,0x07,0x7f,0x6f};
void main(void)
{
 u8 exdat=1,i=0;
   P2=0X00;
		while(1)
		{
			for(i=0;i<10;i++)	
			{ 
					exdat=Slave_Receive_Dat();
					P2=num[exdat];
					Delay_ms(500);
	
					Slave_Send_Dat(i);
					Delay_ms(500);	
			}	
		}
}