#include "myiic.h"
#include "delay.h"


#if i2c 
//初始化IIC
void I1C_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 	//PB5,PB6,PB7 输出高
}

void SDA_IN(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //推挽输出

	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_7); 	//PB5,PB6,PB7 输出高
}
//产生IIC起始信号
void I1C_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL_1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void I1C_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 I1C_Wait_Ack(void)
{
	
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL_1;delay_us(1);	 
	
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))   //f
//	while(READ_SDA)   //f
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I1C_Stop();
			return 1;
		}
	}
	IIC_SCL_0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void I1C_Ack(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL_1;
	delay_us(2);
	IIC_SCL_0;
}
//不产生ACK应答		    
void I1C_NAck(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL_1;
	delay_us(2);
	IIC_SCL_0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void I1C_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_1;
		delay_us(2); 
		IIC_SCL_0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 I1C_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_0; 
        delay_us(2);
		IIC_SCL_1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        I1C_NAck();//发送nACK
    else
        I1C_Ack(); //发送ACK   
    return receive;
}
#else
//初始化IIC
void I1C_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //5:DA  6时钟  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 	//PB5,PB6,PB7 输出高
}


void SDA_IN(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   //推挽输出

	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_7); 	//PB5,PB6,PB7 输出高  AD
}

//产生IIC起始信号
void I1C_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;
delay_us(1);	
	IIC_SCL_1;
	delay_us(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL_0;//钳住I2C总线，准备发送或接收数据 
	delay_us(5);
}	  
//产生IIC停止信号
void I1C_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_0;
    delay_us(5);
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	delay_us(5);
	IIC_SCL_1; 
	delay_us(5);
	IIC_SDA=1;//发送I2C总线结束信号
							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 I1C_Wait_Ack(void)
{
	
	u16 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	//IIC_SDA=1;//
	delay_us(1);	 
	
	IIC_SCL_1;//delay_us(1); 
	
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))   //f
		
//	while(READ_SDA)   //
	{
		ucErrTime++;
		if(ucErrTime>205)
		{
			I1C_Stop();
			return 1;
		}
	}

	IIC_SCL_0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void I1C_Ack(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(4);
	IIC_SCL_1;
	delay_us(4);
	IIC_SCL_0;
}
//不产生ACK应答		    
void I1C_NAck(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(4);
	IIC_SCL_1;
	delay_us(4);
	IIC_SCL_0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void I1C_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {     
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(4);   //对TEA5767这三个延时都是必须的
		IIC_SCL_1;
		delay_us(4); 
		IIC_SCL_0;	

    }

} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 I1C_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_0; 
        delay_us(4);
		IIC_SCL_1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(4); 
    }					 
    if (!ack)
        I1C_NAck();//发送nACK
    else
        I1C_Ack(); //发送ACK   
    return receive;
}
#endif


























