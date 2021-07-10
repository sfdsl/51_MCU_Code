#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "config.h"



/*����һ���ṹ��
��ţ��¶�ֵ��  ���š��������֡�С������
*/
typedef struct {
			uchar tempflag;//�¶�ֵ�ķ���
			uchar fraction;//�¶�ֵ��С��
	    uchar tempr;	 //�¶�ֵ����������
}Temperature_value;


Temperature_value Read18B20_Temperature(void);         //��ȡ�Ĵ����д洢���¶�����


void tempchange(void);    //DS18B20 ��ʼ��ȡ�¶Ȳ�ת��
unsigned int get_temp(void) ;    //��ȡ�Ĵ����д洢���¶�����

/*�õ������¶�����*/
float  Handle_temp(void);
#endif