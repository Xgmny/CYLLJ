#include "cs1237_1.h"
#include "delay.h"
//#include "uart.h"

//作者：技小新
//官网：http://www.jixin.pro
//我的微信：253057617


// PA0-----CLK 
// PA1-----OUT

void Delay1us_1(void)
{
	__IO uint32_t t=5;   //5是  1us
	
	while(t--);
}

void Delay1ms_1(void)
{
	__IO uint32_t t=8000;
	
	while(t--);
}

void delay_ms_cs_1(__IO uint16_t ms)
{
	do{
		Delay1ms_1();
	}while(ms--);
}

// 初始化PA2 PA3
// PA0-----CLK
// PA1-----OUT
void CS1237_1_Init_JX(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;					
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	// PA0 ----- CLK  设置为输出
	// PA1 ----- OUT  设置为输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK拉高
	GPIO_SetBits(GPIOA, GPIO_Pin_1);	// OUT拉高
}

//配置CS1237_1芯片
void CS1237_1_Config(void)
{
	unsigned char i;
	unsigned char dat;
	unsigned int count_i=0;//溢出计时器
	
	//dat = 0X1C;     //芯片地配置 内部REF(00) 输出40HZ(01) PGA=128倍(11) 通道A 0X1C(00)  
    //dat = 0X18;	  //芯片地配置 内部REF(00) 输出40HZ(01) PGA=64倍(10)  通道A 0X1C 
	//dat = 0X14;	  //芯片地配置 内部REF(00) 输出40HZ(01) PGA=2倍(01)   通道A 0X1C
	//dat = 0X10;     //芯片地配置 内部REF(00) 输出40HZ(01) PGA=1倍(00)   通道A 0X1C
	dat =0x18;
  
/***********************************************************************************/	
	
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //OUT引脚拉高
	OUT_IN_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);// 时钟拉低
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1) //等待CS237准备好   300次dalay不==0就退出
	{
		delay_ms(1);
		count_i++;
		if(count_i > 3000)
		{
			OUT_OUT_1();
			GPIO_SetBits(GPIOA, GPIO_Pin_1); // OUT引脚拉高
			GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK引脚拉高
			return;//超时，则直接退出程序
		}
	}
	for(i=0;i<29;i++)// 1 - 29
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
	}
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_SetBits(GPIOA, GPIO_Pin_1);  GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//30     
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_SetBits(GPIOA, GPIO_Pin_1);  GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//31
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_ResetBits(GPIOA, GPIO_Pin_1);GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//32
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_ResetBits(GPIOA, GPIO_Pin_1);GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//33
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_SetBits(GPIOA, GPIO_Pin_1);  GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//34
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_ResetBits(GPIOA, GPIO_Pin_1);GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//35
	GPIO_SetBits(GPIOA, GPIO_Pin_0);Delay1us_1();GPIO_SetBits(GPIOA, GPIO_Pin_1);  GPIO_ResetBits(GPIOA, GPIO_Pin_0);Delay1us_1();//36
	//DA 1100101
	//37     写入了0x65
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
	Delay1us_1();
	
	for(i=0;i<8;i++)// 38 - 45个脉冲了，写8位数据        写设置
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		if(dat&0x80)
			GPIO_SetBits(GPIOA, GPIO_Pin_1);// OUT = 1
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		dat <<= 1;
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
	}
	GPIO_SetBits(GPIOA, GPIO_Pin_1);// OUT = 1
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
	Delay1us_1();
}

// 读取芯片的配置数据
unsigned char Read_Config_1(void)
{
	unsigned char i;
	unsigned char dat=0;//读取到的数据
	unsigned int count_i=0;//溢出计时器
//	unsigned char k=0,j=0;//中间变量
	
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //OUT引脚拉高
	OUT_IN_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);//时钟拉低
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)//等待芯片准备好数据
	{
		delay_ms(1);
		count_i++;
		if(count_i > 400)
		{
			OUT_OUT_1();
			GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
			GPIO_SetBits(GPIOA, GPIO_Pin_1);	// OUT=1;
			return 1;//超时，则直接退出程序
		}
	}

	for(i=0;i<29;i++)// 产生第1到29个时钟
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
	}
	
	OUT_OUT_1();
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); 
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();// 这是第30个时钟
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();// 这是第31个时钟
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();//32
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();//33
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); 
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();//34
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();//35
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // CLK=0;
	Delay1us_1();//36
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
	Delay1us_1();//37     写入0x56 即读命令
	
	dat=0;
	OUT_IN_1();
	for(i=0;i<8;i++)// 第38 - 45个脉冲了，读取数据
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
		dat <<= 1;
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)
			dat++;
	}
	
	//第46个脉冲
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
	Delay1us_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
	Delay1us_1();
	
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //OUT引脚拉高
	
	return dat;
}

//读取ADC数据，返回的是一个有符号数据
int32_t Read_CS1237_1(void)
{
	unsigned char i;
	uint32_t dat=0;//读取到的数据
	unsigned int count_i=0;//溢出计时器
	int32_t temp;
	
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //OUT引脚拉高
	OUT_IN_1();
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);//时钟拉低
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)//等待芯片准备好数据
	{
		delay_ms(1);
		count_i++;
		if(count_i > 400)  //之前是300
		{
			OUT_OUT_1();
			GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
			GPIO_SetBits(GPIOA, GPIO_Pin_1);	// OUT=1;
			return 1;//超时，则直接退出程序
		}
	}
	
	dat=0;
	for(i=0;i<24;i++)//获取24位有效转换
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		dat <<= 1;
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)
			dat ++;
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
	}
	
	for(i=0;i<3;i++)//接着前面的时钟 再来3个时钟
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	// CLK=1;
		Delay1us_1();
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// CLK=0;
		Delay1us_1();
	}
	
	OUT_OUT_1();
	GPIO_SetBits(GPIOA, GPIO_Pin_1); // OUT = 1;

	
//	if(dat&0x00800000)// 判断是负数 最高位24位是符号位
//	{
//		temp=-(((~dat)&0x007FFFFF) + 1);// 补码变源码
//	}
//	else
		temp=dat; // 正数的补码就是源码
	
	return temp;

}




