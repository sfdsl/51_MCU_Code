#ifndef __LCD1602_H_
#define __LCD1602_H_


#include  "config.h"


/**********************************
��������
**********************************/
/*LCD1602��ʼ���ӳ���*/		
void LCD_Init();					
void Write_LCD_Command(uchar com);	  //д������
void Write_LCD_Data(uchar dat);			//д������
//void  Control_1602BackLED(uchar n);

void DisplayOneChar(uchar X,uchar Y,uchar DData);
/****************д������ַ����ݵ�ָ����λ��***************/
void Lcd1602SetCursor(uchar X,uchar Y);
void DisplayChars(uchar X,uchar Y,uchar *str);

/*********************************************************************
��������:Disp_number()
��������:��ʾ������
��ڲ���:num:��ʾ������ n:����λ��
����ֵ:��
************************************************************************/
void Disp_number(uchar X,uchar Y,uint num,u8 n);




#endif

