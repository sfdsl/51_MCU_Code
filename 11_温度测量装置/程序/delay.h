#ifndef _DELAY_H_
#define _DELAY_H_

   #include "config.h"

  void Delay1ms(uint c)	;	//@12.000MHz
	void Delay2us(uint us);		//@12.000MHz
void Delay1us(uint us);		//@12.000MHz
	
#define   Lcd1602_Delay1ms   Delay1ms


#endif

