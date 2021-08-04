#include "24cxx.h" 
#include "delay.h"



//初始化IIC接口
void AT24CXX_Init(void)
{
	u8 kl[8];
	I1C_Init();
	
	AT24CXX_Read(02,kl,4);
	if((kl[0]!=0x31)|(kl[0]!=0x35)|(kl[0]!=0x4f)|(kl[0]!=0x4c))
	{
		kl[0]=0x31;kl[1]=0x35;kl[2]=0x4f;kl[3]=0x4c;
		AT24CXX_Write(02,kl,4);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x2e;kl[3]=0x30;kl[4]=0x30;
		AT24CXX_Write(0x10,kl,5);AT24CXX_Write(0x18,kl,5);
		AT24CXX_Write(0x70,kl,5);AT24CXX_Write(0x78,kl,5);
		kl[0]=0x31;kl[1]=0x2e;kl[2]=0x30;kl[3]=0x30;kl[4]=0x30;kl[5]=0x30;kl[6]=0x30;
		AT24CXX_Write(0x20,kl,5);AT24CXX_Write(0x80,kl,5);
		AT24CXX_Write(0x28,kl,5);AT24CXX_Write(0x30,kl,5);AT24CXX_Write(0x38,kl,5);
		AT24CXX_Write(0x40,kl,5);AT24CXX_Write(0x48,kl,5);AT24CXX_Write(0x50,kl,5);
		AT24CXX_Write(0x58,kl,5);AT24CXX_Write(0x60,kl,5);AT24CXX_Write(0x68,kl,5);
		AT24CXX_Write(0x88,kl,5);AT24CXX_Write(0x90,kl,5);AT24CXX_Write(0x98,kl,5);
		AT24CXX_Write(0xa0,kl,5);AT24CXX_Write(0xa8,kl,5);AT24CXX_Write(0xb0,kl,5);
		AT24CXX_Write(0xb8,kl,5);AT24CXX_Write(0xc0,kl,5);AT24CXX_Write(0xc8,kl,5);
		kl[0]=0x32;kl[1]=0x30;kl[2]=0x30;kl[3]=0x30;kl[4]=0x2e;kl[5]=0x30;kl[6]=0x30;
		AT24CXX_Write(0xD0,kl,7);
		AT24CXX_Write(0xD8,kl,7);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x30;kl[3]=0x30;kl[4]=0x30;kl[5]=0x30;kl[6]=0x2e;kl[7]=0x30;
		AT24CXX_Write(0xe0,kl,8);
	}
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    I1C_Start();  
	if(EE_TYPE>AT24C16)
	{
		I1C_Send_Byte(0XA0);	   //发送写命令
		I1C_Wait_Ack();
		I1C_Send_Byte(ReadAddr>>8);//发送高地址
		I1C_Wait_Ack();		 
	}else I1C_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	I1C_Wait_Ack(); 
    I1C_Send_Byte(ReadAddr%256);   //发送低地址
	I1C_Wait_Ack();	    
	I1C_Start();  	 	   
	I1C_Send_Byte(0XA1);           //进入接收模式			   
	I1C_Wait_Ack();	 
    temp=I1C_Read_Byte(0);		   
    I1C_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    I1C_Start();  
	if(EE_TYPE>AT24C16)
	{
		I1C_Send_Byte(0XA0);	    //发送写命令
		I1C_Wait_Ack();
		I1C_Send_Byte(WriteAddr>>8);//发送高地址
 	}else
	{
		I1C_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	I1C_Wait_Ack();	   
    I1C_Send_Byte(WriteAddr%256);   //发送低地址
	I1C_Wait_Ack(); 	 										  		   
	I1C_Send_Byte(DataToWrite);     //发送字节							   
	I1C_Wait_Ack();  		    	   
    I1C_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u8 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
	delay_ms(50);
}
 











