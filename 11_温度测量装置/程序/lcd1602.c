#include "lcd1602.h"
#include "delay.h"


u8 code number[10]={"0123456789"};

/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
#ifndef LCD1602_4PINS	 //��û�ж������LCD1602_4PINSʱ
void Write_LCD_Command(uchar com)	  //д������
{
	LCD1602_EN = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_EN = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_EN = 0;
}
#else 
void Write_LCD_Command(uchar com)	  //д������
{
	LCD1602_EN = 0;	 //ʹ������
	LCD1602_RS = 0;	 //ѡ��д������
	LCD1602_RW = 0;	 //ѡ��д��

	LCD1602_DATAPINS = com;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;

	LCD1602_DATAPINS = com << 4; //���͵���λ
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;
}
#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void Write_LCD_Data(uchar dat)			//д������
{
	LCD1602_EN = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_EN = 0;
}
#else
void Write_LCD_Data(uchar dat)			//д������
{
	LCD1602_EN = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_EN = 0;
}
#endif

void LCD_Init() //1602LCD ��ʼ��
{
		Write_LCD_Command(0x01);//����
		Write_LCD_Command(0x38);//����8λ��ʽ��2�У�5*7
		Write_LCD_Command(0x0c);//������ʾ���ع�꣬����˸
		Write_LCD_Command(0x06);//�趨���뷽ʽ����������λ
}


/****************дһ���ַ����ݵ�ָ����λ��***************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
		Y&=1;						
		X&=15;						
		if(Y)X|=0x40;					
		X|=0x80;			
		Write_LCD_Command(X);		
		Write_LCD_Data(DData+0x30);		
}

/****************LCD1602���õ�ַ***************/
void Lcd1602SetCursor(uchar X,uchar Y)
{
	Y&=1;						
	X&=15;						
	if(Y)X|=0x40;					
	X|=0x80;			
	Write_LCD_Command(X);

}
	
/****************д������ַ����ݵ�ָ����λ��***************/
void DisplayChars(uchar X,uchar Y,uchar *str)
{		
   Lcd1602SetCursor(X, Y);   //������ʼ��ַ
	 while (*str != '\0')  
    {
        Write_LCD_Data(*(str++));
    }			
}



///*********************************************************************
//��������:Disp_number()
//��������:��ʾ������
//��ڲ���:num:��ʾ������ n:����λ��
//����ֵ:��
//************************************************************************/
void Disp_number(uchar X,uchar Y,uint num,u8 n)
{ 
			u8 a; //��λ 
			u8 b; //ʮλ
			u8 c; //��λ
			u8 d; //ǧλ
			u8 e; //��λ

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
