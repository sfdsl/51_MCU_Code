#include "DS18B20.h"
#include "delay.h"


uchar code fractioncode[]={0,0,1,2,2,3,4,4,5,6,6,7,8,8,9,9};


//void dsreset(void)    //18B20��λ����ʼ������
//{
//  ds=0;
//  Delay1us(600);//������ʱ480us
//  ds=1;
//	
//	while(ds)//�ȴ�����Ӧ��Լ15~60us֮��
//	putchar(0xaa);
//	while(!ds);//Ӧ��������֮�󣬵ȴ���������Լ60~240us��
//	putchar(0xbb);
//}

uchar dsreset(void)   //18B20��λ����ʼ������
{
uchar status;
		ds = 1;        // ��⵽�½��أ���ʼ��
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

uchar tempread(void)   //�����ݺ���
{
   uchar i,rdata=0;
   for(i=0;i<8;i++)
	 {
			 ds=0;
			 Delay2us(2);//������ʱ1us
			 ds=1;//�ͷ����߿���Ȩ��15s��Ҫ��ȡ����
		 _nop_();
		 _nop_();
			 if(ds==1) 
				 rdata|=0x01<<i;//�������������λ����ǰ�棬�����պ�һ���ֽ���rdata��
			 Delay1us(30);//��ʱҪ����45us����0ʱ��45us����������������
			ds=1; 
	 }
   return rdata;
}

void tempwritebyte(unsigned char com)   //��18B20дһ���ֽ�����
{
			uchar i;
	 for(i=0;i<8;i++)
		{
				ds=0;//��ʼд����;
			  //Delay1us(2);//������ʱ1us
			  ds=com&0x01;//��ʼд����
				Delay2us(5);//��ʱ������10us�ڲ���
			  ds=1;//�ͷ����߿���Ȩ
			  com>>=1;//����1λ��д��һλ
		}
}

Temperature_value Read18B20_Temperature(void) //��ȡ�Ĵ����д洢���¶�����
{
			unsigned char Temp_L,Temp_H,temp;
			Temperature_value  stemp;
	
			uint tempv=0;
					
			dsreset();						//��λ
			tempwritebyte(0xcc);	// д������ROMָ��
			tempwritebyte(0x44);  // д�¶�ת��ָ��
			while(!ds);//�ȴ�ת�����
				
			dsreset();						//��λ
			tempwritebyte(0xcc);	// д������ROMָ��
			tempwritebyte(0xbe);	//��ȡ�ݴ����ֽ�����
			
			Temp_L=tempread();    //����8λ
			Temp_H=tempread();    //����8λ
			dsreset();						//��λ
			
			tempv=Temp_H;
			tempv=tempv<<8|Temp_L; //�����ֽ����Ϊ1����.int������
			
			temp=(uchar)(tempv>>4);//ȥ��С�����֣�����char������
			
			if((Temp_H&0x80)==0x80)//����Ǹ��¶�
			{
					stemp.tempflag=1;//������ʾ
					stemp.tempr=~temp+1;//ʵ���¶�Ϊ��ȡֵ�Ĳ���
					stemp.fraction=fractioncode[(~Temp_L+1)&0x0f];//ȡС�����룬��16�̶�ת��Ϊ10�̶ȣ�����λ0.1��
			}else
			{
				stemp.tempflag=0;//������ʾ
				stemp.tempr=temp;
				stemp.fraction=fractioncode[Temp_L&0x0f];//ȡС�����룬��16�̶�ת��Ϊ10�̶ȣ�����λ0.1��
			}
	return stemp;
}

