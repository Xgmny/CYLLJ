#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"




#define KEYA  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//读取按键+
#define KEYR  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键>
#define KEYY  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键END 

void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  	//按键扫描函数					    
#endif
