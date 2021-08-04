
#include "24c64.h" 
#include "delay.h"

	extern u8 ljl[];
	extern int32_t LJ;
	extern int32_t LL;
	extern u16 SZ_JZ_Z[], SZ_JZ_F[];                     //   %比校正
	extern u16 SZ_LD_Z, SZ_LD_F, SZ_QC_Z, SZ_QC_F;       //   0点    切除
	extern int32_t  SZ_LL_Z,SZ_LL_F;		                 //   正反向量程  
           u8  JNW[8] ;
		   u32 JNS;
           u32 NIAN; 
//初始化IIC接口
void AT24CXX_Init(void)
{
	u8 kl[8];
	I1C_Init();
    WP=0;
	delay_ms(2);
	AT24CXX_Read(0X0100,kl,4);
	delay_ms(2);
	if((kl[0]!=0x38)|(kl[1]!=0x39)|(kl[2]!=0x4f)|(kl[3]!=0x4b))
	{
		kl[0]=0x38;kl[1]=0x39;kl[2]=0x4f;kl[3]=0x4b;
		AT24CXX_Write(0X0100,kl,4);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x30;
		AT24CXX_Write(0X0108,kl,3);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x2e;kl[3]=0x30;kl[4]=0x30;//零点切除
		AT24CXX_Write(0x0110,kl,5);
		AT24CXX_Write(0x0170,kl,5);
		AT24CXX_Write(0x0118,kl,5);
		AT24CXX_Write(0x0178,kl,5);
		kl[0]=0x31;kl[1]=0x2e;kl[2]=0x30;kl[3]=0x30;kl[4]=0x30;kl[5]=0x30;kl[6]=0x30;
		AT24CXX_Write(0x0120,kl,5);AT24CXX_Write(0x0180,kl,5);
		AT24CXX_Write(0x0128,kl,5);AT24CXX_Write(0x0130,kl,5);AT24CXX_Write(0x0138,kl,5);
		AT24CXX_Write(0x0140,kl,5);AT24CXX_Write(0x0148,kl,5);AT24CXX_Write(0x0150,kl,5);
		AT24CXX_Write(0x0158,kl,5);AT24CXX_Write(0x0160,kl,5);AT24CXX_Write(0x0168,kl,5);
		AT24CXX_Write(0x0188,kl,5);AT24CXX_Write(0x0190,kl,5);AT24CXX_Write(0x0198,kl,5);
		AT24CXX_Write(0x01a0,kl,5);AT24CXX_Write(0x01a8,kl,5);AT24CXX_Write(0x01b0,kl,5);
		AT24CXX_Write(0x01b8,kl,5);AT24CXX_Write(0x01c0,kl,5);AT24CXX_Write(0x01c8,kl,5);
		AT24CXX_Write(0x0050,kl,5);//WDXS
		kl[0]=0x2B;kl[1]=0x30;kl[2]=0x30;kl[3]=0x2E;kl[4]=0x30;kl[5]=0x30;
		AT24CXX_Write(0x0058,kl,6);//WDLD
		kl[0]=0x2B;kl[1]=0x30;kl[2]=0x30;kl[4]=0x2E;kl[3]=0x30;kl[5]=0x30;
		AT24CXX_Write(0x0060,kl,6);//WDZ
		AT24CXX_Write(0x0070,kl,6);//QJZ
		kl[0]=0x2D;
		AT24CXX_Write(0x0068,kl,6);//WDF
		AT24CXX_Write(0x0078,kl,6);//QJF
		kl[0]=0x32;kl[1]=0x30;kl[2]=0x30;kl[3]=0x2e;kl[4]=0x30;kl[5]=0x30;kl[6]=0x30;
		AT24CXX_Write(0x01D0,kl,7);		AT24CXX_Write(0x01D8,kl,7);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x30;kl[3]=0x30;kl[4]=0x30;kl[5]=0x30;kl[6]=0x2e;kl[7]=0x30;
		AT24CXX_Write(0x01e0,kl,8);
		AT24CXX_Write(0x0200,kl,8);
		kl[0]=0x30;kl[1]=0x30;kl[2]=0x30;kl[3]=0x30;kl[4]=0x30;kl[5]=0x30;kl[6]=0x30;kl[7]=0x30;
	    AT24CXX_Write(0x01f0,kl,8);         //计年
		AT24CXX_Write(0x0200+0x0008,kl,8);  //计数
	}
		myid=A_N_24C64(3,kl,0x0108);
		myid*=16;   //16进制
		myid=0x11940400+myid;
		LJ = A_N_24C64(8,ljl,0x0200+NIAN);
		JNS= A_N_24C64(8,JNW,0x0200+NIAN+0x0008);   //读出 读写次数
		BL_24c64();
	NIAN=A_N_24C64(4,kl,0x01f0);   //1百万
	NIAN*=16;   //16进制
	delay_ms(2);
	
	WP=1;
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
	I1C_Stop();            //
	I1C_Start();
	I1C_Send_Byte(0XA0);	   //发送写命令
	I1C_Wait_Ack();
	I1C_Send_Byte(ReadAddr>>8);//发送高地址
	I1C_Wait_Ack();
    I1C_Send_Byte(ReadAddr%256);   //发送低地址
	I1C_Wait_Ack();    
	I1C_Start();  	 	   
	I1C_Send_Byte(0XA1);           //进入接收模式			   
	I1C_Ack();	 
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

		I1C_Send_Byte(0XA0);	    //发送写命令
		I1C_Wait_Ack();
		I1C_Send_Byte(WriteAddr>>8);//发送高地址

	 
	I1C_Wait_Ack();	   
    I1C_Send_Byte(WriteAddr%256);   //发送低地址
	I1C_Wait_Ack(); 	 										  		   
	I1C_Send_Byte(DataToWrite);     //发送字节							   
	I1C_Wait_Ack();  		    	   
   I1C_Stop();//产生一个停止条件 
	delay_ms(3);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u8 DataToWrite,u8 Len)
{  	
	u8 t;
	WP=0;
	delay_ms(2);
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}
	WP=1;	
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
	//I1C_Stop();            //
	I1C_Start();
	I1C_Send_Byte(0XA0);	   //发送写命令
	I1C_Wait_Ack();
	I1C_Send_Byte(ReadAddr>>8);//发送高地址
	I1C_Wait_Ack();
    I1C_Send_Byte(ReadAddr%256);   //发送低地址
	I1C_Wait_Ack();    
	I1C_Start();  	 	   
	I1C_Send_Byte(0XA1);           //进入接收模式	
    I1C_Ack();		

	while(NumToRead)
	{
		*pBuffer=I1C_Read_Byte(NumToRead-1);
		NumToRead--;
		ReadAddr++;
		pBuffer++;
	}	
	 I1C_Stop();//产生一个停止条件	
	delay_us(10);
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	WP=0;
//	I1C_Stop();
//	delay_ms(5);
	
        I1C_Start();  
		I1C_Send_Byte(0XA0);	    //发送写命令
		I1C_Wait_Ack();
		I1C_Send_Byte(WriteAddr>>8);//发送高地址
     	I1C_Wait_Ack();	   
        I1C_Send_Byte(WriteAddr%256);   //发送低地址
	    I1C_Wait_Ack(); 	
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
	I1C_Stop();//产生一个停止条件 
	
	WP=1;
//	delay_ms(1);
}


//ASCLL~数字
//w 位数     a指针地址   读d24c64内在地址  
int32_t  A_N_24C64 (u8 w,u8 *a,u16 d)
{
 int32_t  n ,nn;
	u32 bei=1;
 	AT24CXX_Read(d,a,w);
	 for(;w>0;w--)
		{
		  if(a[w-1]<=58&&a[w-1]>=48)			
		  {
			n=bei*(a[w-1]-48);
			bei*=10 ;
			nn +=n ;
		  }
		}return nn;
}
	   
void BL_24c64(void){
	u8 kl[8];
	
	    SZ_LD_Z = A_N_24C64(5,kl,0x0110);     //零点
	    SZ_QC_Z = A_N_24C64(5,kl,0x0118);   // 切除
        SZ_LL_Z = A_N_24C64(6,kl,0X01D0);    //流量量程

		SZ_JZ_Z[0]=A_N_24C64(5,kl,0x0120);	//<10%
		SZ_JZ_Z[1]=A_N_24C64(5,kl,0x0128);	//<~20%
		SZ_JZ_Z[2]=A_N_24C64(5,kl,0x0130);	//<~30%
		SZ_JZ_Z[3]=A_N_24C64(5,kl,0x0138);	//<~40%
		SZ_JZ_Z[4]=A_N_24C64(5,kl,0x0140);	//<~50%
		SZ_JZ_Z[5]=A_N_24C64(5,kl,0x0148);	//<~60%
		SZ_JZ_Z[6]=A_N_24C64(5,kl,0x0150);	//<~70%
		SZ_JZ_Z[7]=A_N_24C64(5,kl,0x0158);	//<~80%
		SZ_JZ_Z[8]=A_N_24C64(5,kl,0x0160);	//<~90%
		SZ_JZ_Z[9]=A_N_24C64(5,kl,0x0168);	//>90%	
	
		SZ_LD_F = A_N_24C64(5,kl,0x0170);     //零点
	    SZ_QC_F = A_N_24C64(5,kl,0x0178);   // 切除
        SZ_LL_F = A_N_24C64(6,kl,0X01D8);    //流量量程

		SZ_JZ_F[0]=A_N_24C64(5,kl,0x0180);	//<10%
		SZ_JZ_F[1]=A_N_24C64(5,kl,0x0188);	//<~20%
		SZ_JZ_F[2]=A_N_24C64(5,kl,0x0190);	//<~30%
		SZ_JZ_F[3]=A_N_24C64(5,kl,0x0198);	//<~40%
		SZ_JZ_F[4]=A_N_24C64(5,kl,0x01A0);	//<~50%
		SZ_JZ_F[5]=A_N_24C64(5,kl,0x01A8);	//<~60%
		SZ_JZ_F[6]=A_N_24C64(5,kl,0x01B0);	//<~70%
		SZ_JZ_F[7]=A_N_24C64(5,kl,0x01B8);	//<~80%
		SZ_JZ_F[8]=A_N_24C64(5,kl,0x01C0);	//<~90%
		SZ_JZ_F[9]=A_N_24C64(5,kl,0x01C8);	//>90%	
		
		LJ = A_N_24C64(8,ljl,0x0200+NIAN);  //累计量
}	









