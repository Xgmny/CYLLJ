#ifndef __cs1237_1_H
#define __cs1237_1_H


#include "stm32f10x.h"

//OUT引脚输入输出 方向设置  PA3
#define OUT_IN_1()  {GPIOA->CRL&=0XFFFFFF0F;GPIOB->CRH|=8<<28;} 
//第0引角 ;1000  ;   输入模式;上拉/下拉输入模式
#define OUT_OUT_1() {GPIOA->CRL&=0XFFFFFF0F;GPIOB->CRH|=3<<28;} 
//第1引角 ;0011  ;   输出模式，最大速度50MHz



void Delay1us_1(void);
void Delay1ms_1(void);
void delay_ms_cs_1(__IO uint16_t ms);
void CS1237_1_Init_JX(void);
void CS1237_1_Config(void);
unsigned char Read_Config_1(void);
int32_t Read_CS1237_1(void);

#endif


