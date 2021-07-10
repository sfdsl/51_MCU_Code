
#include "TLC2543.h"
#include "delay.h"





/**************************************
  名称：read2543
  功能：TLC2543驱动模块
  输入参数：port通道号
  输出参数：ad转换值
*************************************/
uint read2543(uchar port)
{
		uint ad=0,i;
			CLOCK=0;
			_CS=0;
			port<<=4;
		for(i=0;i<12;i++)
		{
				if(D_OUT) 
					ad|=0x01;
				D_IN=(bit)(port&0x80);
				CLOCK=1;
				Delay1us(3);
				CLOCK=0;
				Delay1us(3);
				port<<=1;
				ad<<=1;
		}
			_CS=1;
			ad>>=1;
		return(ad);
}

