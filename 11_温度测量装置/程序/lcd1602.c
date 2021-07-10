#include "lcd1602.h"
#include "delay.h"


u8 code number[10]={"0123456789"};

/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
void Write_LCD_Command(uchar com)	  //写入命令
{
	LCD1602_EN = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_EN = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_EN = 0;
}
#else 
void Write_LCD_Command(uchar com)	  //写入命令
{
	LCD1602_EN = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;

	LCD1602_DATAPINS = com << 4; //发送低四位
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void Write_LCD_Data(uchar dat)			//写入数据
{
	LCD1602_EN = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_EN = 0;
}
#else
void Write_LCD_Data(uchar dat)			//写入数据
{
	LCD1602_EN = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;
}
#endif

void LCD_Init() //1602LCD 初始化
{
		Write_LCD_Command(0x01);//清屏
		Write_LCD_Command(0x38);//设置8位格式，2行，5*7
		Write_LCD_Command(0x0c);//整体显示，关光标，不闪烁
		Write_LCD_Command(0x06);//设定输入方式，增量不移位
}


/****************写一个字符数据到指定的位置***************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
		Y&=1;						
		X&=15;						
		if(Y)X|=0x40;					
		X|=0x80;			
		Write_LCD_Command(X);		
		Write_LCD_Data(DData+0x30);		
}

/****************LCD1602设置地址***************/
void Lcd1602SetCursor(uchar X,uchar Y)
{
	Y&=1;						
	X&=15;						
	if(Y)X|=0x40;					
	X|=0x80;			
	Write_LCD_Command(X);

}
	
/****************写多个个字符数据到指定的位置***************/
void DisplayChars(uchar X,uchar Y,uchar *str)
{		
   Lcd1602SetCursor(X, Y);   //设置起始地址
	 while (*str != '\0')  
    {
        Write_LCD_Data(*(str++));
    }			
}



///*********************************************************************
//函数名称:Disp_number()
//功能描述:显示四数字
//入口参数:num:显示的数字 n:数字位数
//返回值:无
//************************************************************************/
void Disp_number(uchar X,uchar Y,uint num,u8 n)
{ 
			u8 a; //个位 
			u8 b; //十位
			u8 c; //百位
			u8 d; //千位
			u8 e; //万位

	Y&=1;						
	X&=15;						
	if(Y)X|=0x40;					
	X|=0x80;			
	Write_LCD_Command(X);
			switch(n)
			{
			case 1:Write_LCD_Data(num);
			break;
			case 2:b=num/10;
			a=num%10;
			Write_LCD_Data(number[b]);
			Write_LCD_Data(number[a]);
			break;
			case 3:c=num/100;
			b=num%100/10;
			a=num%10;
			Write_LCD_Data(number[c]);
			Write_LCD_Data(number[b]);
			Write_LCD_Data(number[a]);
			break;
			case 4:d=num/1000;
			c=num%1000/100;
			b=num%1000%100/10;
			a=num%10;
			Write_LCD_Data(number[d]);
			Write_LCD_Data(number[c]);
			Write_LCD_Data(number[b]);
			Write_LCD_Data(number[a]);
			break;
			case 5:
			e=num/10000;
			d=num%10000/1000;
			c=num%1000/100;
			b=num%100/10;
			a=num%10;
			Write_LCD_Data(number[e]);
			Write_LCD_Data(number[d]);
			Write_LCD_Data(number[c]);
			Write_LCD_Data(number[b]);
			Write_LCD_Data(number[a]);
			break;
			}
}
