#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
/////////////////////////////////////////////////////////////////////////////////
#define i2c 0
//IO方向设置
#if i2c
//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
 void SDA_IN(void);
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 
#define WP    	   PBout(5)  
//#define IIC_SCL    PBout(6) //SCL
#define IIC_SCL_1    GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define IIC_SCL_0    GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

//IIC所有操作函数
void I1C_Init(void);                //初始化IIC的IO口				 
void I1C_Start(void);				//发送IIC开始信号
void I1C_Stop(void);	  			//发送IIC停止信号
void I1C_Send_Byte(u8 txd);			//IIC发送一个字节
u8 I1C_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 I1C_Wait_Ack(void); 				//IIC等待ACK信号
void I1C_Ack(void);					//IIC发送ACK信号
void I1C_NAck(void);				//IIC不发送ACK信号

void I1C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 I1C_Read_One_Byte(u8 daddr,u8 addr);	  
#else 


//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
 void SDA_IN(void);
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 
#define WP    	   PBout(5)  
//#define IIC_SCL    PBout(6) //SCL
#define IIC_SCL_1    GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define IIC_SCL_0    GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

//IIC所有操作函数
void I1C_Init(void);                //初始化IIC的IO口				 
void I1C_Start(void);				//发送IIC开始信号
void I1C_Stop(void);	  			//发送IIC停止信号
void I1C_Send_Byte(u8 txd);			//IIC发送一个字节
u8 I1C_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 I1C_Wait_Ack(void); 				//IIC等待ACK信号
void I1C_Ack(void);					//IIC发送ACK信号
void I1C_NAck(void);				//IIC不发送ACK信号

void I1C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 I1C_Read_One_Byte(u8 daddr,u8 addr);	  





#endif

#endif
















