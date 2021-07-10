#ifndef    _CONFIG_H_
#define   _CONFIG_H_



#include <reg51.h>
#include <intrins.H>
#include <stdio.h>



#define  uchar  unsigned char 
#define  uint   unsigned int

typedef unsigned char	u8;
typedef unsigned int	u16;
typedef unsigned int	uint16_t;
typedef unsigned char uint8_t;
typedef unsigned char INT8U; // �޷���8λ���ͱ��� // 
typedef signed char INT8S; // �з���8λ���ͱ��� // 
typedef unsigned int INT16U; // �޷���16λ���ͱ��� // 
typedef signed int INT16S; // �з���16λ���ͱ��� // 
typedef unsigned long INT32U; // �޷���32λ���ͱ��� // 
typedef signed long INT32S; // �з���32λ���ͱ��� // 
typedef float FP32; // �����ȸ�����(32λ����) // 
typedef double FP64; // ˫���ȸ�����(64λ����) // 
typedef unsigned long u32; // �޷���32λ���ͱ��� // ; // �޷���32λ���ͱ��� // 

/**********************************************************
�ⲿ�豸��IO�ڶ���
***********************************************************/

sbit Beep=P2^0;
sbit Relay_Ctrl=P2^3;
sbit LED=P2^2;
sbit ds=P1^3;

//LCD1602�Ŀ��ƽӿ�
#define LCD1602_DATAPINS P0
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;
sbit LCD1602_EN=P2^7;


//�����˿�
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

//�ȵ�ż�ӿ�

sbit MAX6675_CS =P3^5;
sbit MAX6675_CLK=P3^6;
sbit MAX6675_DAT=P3^7;


/**************************************
        2543�������ź궨��
*************************************/
sbit CLOCK= P3^5; /*2543ʱ��*/
sbit D_IN=P3^3; /*2543����*/
sbit D_OUT=P3^2; /*2543���*/
sbit _CS=P3^4; /*2543Ƭѡ*/



#endif
