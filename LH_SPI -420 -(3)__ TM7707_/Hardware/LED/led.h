#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#define LED0 PCout(13)// PB5


void LED_Init(void);//≥ı ºªØ
void ADCx_Init(void);
void PVD_Init(void);
void PVD_NVIC(void);
u16 Get_ADC_Value(u8 ch,u8 times);

		 				    
#endif
