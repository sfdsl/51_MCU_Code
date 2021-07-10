#include "DS18B20.h"
#include "delay.h"


uchar code fractioncode[]={0,0,1,2,2,3,4,4,5,6,6,7,8,8,9,9};


//void dsreset(void)    //18B20复位，初始化函数
//{
//  ds=0;
//  Delay1us(600);//至少延时480us
//  ds=1;
//	
//	while(ds)//等待器件应答，约15~60us之后
//	putchar(0xaa);
//	while(!ds);//应答秒冲出现之后，等待器件拉高约60~240us后
//	putchar(0xbb);
//}

uchar dsreset(void)   //18B20复位，初始化函数
{
uchar status;
		ds = 1;        // 检测到下降沿，初始化
		Delay2us(16);
		ds = 0;
		Delay2us(90);
		ds = 1;
		Delay2us(8);
	status=ds;
		Delay2us(100);
		ds = 1;
	return status;
}

uchar tempread(void)   //读数据函数
{
   uchar i,rdata=0;
   for(i=0;i<8;i++)
	 {
			 ds=0;
			 Delay2us(2);//至少延时1us
			 ds=1;//释放总线控制权，15s内要读取数据
		 _nop_();
		 _nop_();
			 if(ds==1) 
				 rdata|=0x01<<i;//读出的数据最低位在最前面，这样刚好一个字节在rdata里
			 Delay1us(30);//延时要大于45us，读0时，45us后器件才拉高总线
			ds=1; 
	 }
   return rdata;
}

void tempwritebyte(unsigned char com)   //向18B20写一个字节数据
{
			uchar i;
	 for(i=0;i<8;i++)
		{
				ds=0;//开始写操作;
			  //Delay1us(2);//至少延时1us
			  ds=com&0x01;//开始写数据
				Delay2us(5);//延时器件在10us内采样
			  ds=1;//释放总线控制权
			  com>>=1;//右移1位，写下一位
		}
}

Temperature_value Read18B20_Temperature(void) //读取寄存器中存储的温度数据
{
			unsigned char Temp_L,Temp_H,temp;
			Temperature_value  stemp;
	
			uint tempv=0;
					
			dsreset();						//复位
			tempwritebyte(0xcc);	// 写跳过读ROM指令
			tempwritebyte(0x44);  // 写温度转换指令
			while(!ds);//等待转换完成
				
			dsreset();						//复位
			tempwritebyte(0xcc);	// 写跳过读ROM指令
			tempwritebyte(0xbe);	//读取暂存器字节命令
			
			Temp_L=tempread();    //读低8位
			Temp_H=tempread();    //读高8位
			dsreset();						//复位
			
			tempv=Temp_H;
			tempv=tempv<<8|Temp_L; //两个字节组合为1个字.int型数据
			
			temp=(uchar)(tempv>>4);//去掉小数部分，化成char型数据
			
			if((Temp_H&0x80)==0x80)//如果是负温度
			{
					stemp.tempflag=1;//负号显示
					stemp.tempr=~temp+1;//实际温度为读取值的补码
					stemp.fraction=fractioncode[(~Temp_L+1)&0x0f];//取小数补码，将16刻度转换为10刻度，精度位0.1度
			}else
			{
				stemp.tempflag=0;//正号显示
				stemp.tempr=temp;
				stemp.fraction=fractioncode[Temp_L&0x0f];//取小数补码，将16刻度转换为10刻度，精度位0.1度
			}
	return stemp;
}

