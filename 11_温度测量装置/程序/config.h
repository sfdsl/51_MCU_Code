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
typedef unsigned char INT8U; // 无符号8位整型变量 // 
typedef signed char INT8S; // 有符号8位整型变量 // 
typedef unsigned int INT16U; // 无符号16位整型变量 // 
typedef signed int INT16S; // 有符号16位整型变量 // 
typedef unsigned long INT32U; // 无符号32位整型变量 // 
typedef signed long INT32S; // 有符号32位整型变量 // 
typedef float FP32; // 单精度浮点数(32位长度) // 
typedef double FP64; // 双精度浮点数(64位长度) // 
typedef unsigned long u32; // 无符号32位整型变量 // ; // 无符号32位整型变量 // 

/**********************************************************
外部设备的IO口定义
***********************************************************/

sbit Beep=P2^0;
sbit Relay_Ctrl=P2^3;
sbit LED=P2^2;
sbit ds=P1^3;

//LCD1602的控制接口
#define LCD1602_DATAPINS P0
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;
sbit LCD1602_EN=P2^7;


//按键端口
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

//热电偶接口

sbit MAX6675_CS =P3^5;
sbit MAX6675_CLK=P3^6;
sbit MAX6675_DAT=P3^7;


/**************************************
        2543控制引脚宏定义
*************************************/
sbit CLOCK= P3^5; /*2543时钟*/
sbit D_IN=P3^3; /*2543输入*/
sbit D_OUT=P3^2; /*2543输出*/
sbit _CS=P3^4; /*2543片选*/



#endif
