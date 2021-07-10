#ifndef __LCD1602_H_
#define __LCD1602_H_


#include  "config.h"


/**********************************
函数声明
**********************************/
/*LCD1602初始化子程序*/		
void LCD_Init();					
void Write_LCD_Command(uchar com);	  //写入命令
void Write_LCD_Data(uchar dat);			//写入数据
//void  Control_1602BackLED(uchar n);

void DisplayOneChar(uchar X,uchar Y,uchar DData);
/****************写多个个字符数据到指定的位置***************/
void Lcd1602SetCursor(uchar X,uchar Y);
void DisplayChars(uchar X,uchar Y,uchar *str);

/*********************************************************************
函数名称:Disp_number()
功能描述:显示四数字
入口参数:num:显示的数字 n:数字位数
返回值:无
************************************************************************/
void Disp_number(uchar X,uchar Y,uint num,u8 n);




#endif

