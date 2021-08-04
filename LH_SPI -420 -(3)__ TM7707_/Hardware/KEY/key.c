#include "key.h"
#include "sys.h" 
#include "delay.h"

extern u8 key;


void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTb时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOb.0

}

u8 KEY_Scan(void)
{	 
	u8 aj;
	if((KEYA==0||KEYR==0||KEYY==0))
		{
			 delay_ms(20);//去抖动 
			if(KEYA==0)//+
				{
				
				if(KEYR==0)
					aj=4;
		           else 
					   aj=1;
				}	
			  else
				{
					if	(KEYR==0)
						aj=2;
					else
					{
					if  (KEYY==0)
							aj=3;
						else
							aj=5;}
				}
		   }
	else
		aj=0;
return aj;
}

