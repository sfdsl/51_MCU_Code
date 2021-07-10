#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "config.h"



/*定义一个结构体
存放：温度值的  符号、整数部分、小数部分
*/
typedef struct {
			uchar tempflag;//温度值的符号
			uchar fraction;//温度值的小数
	    uchar tempr;	 //温度值的整数部分
}Temperature_value;


Temperature_value Read18B20_Temperature(void);         //读取寄存器中存储的温度数据


void tempchange(void);    //DS18B20 开始获取温度并转换
unsigned int get_temp(void) ;    //读取寄存器中存储的温度数据

/*得到浮点温度数据*/
float  Handle_temp(void);
#endif