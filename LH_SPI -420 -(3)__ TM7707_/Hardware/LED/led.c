#include "led.h"


//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PC.13 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 }


 void ADCx_Init(void)
 {
     GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量    
     ADC_InitTypeDef       ADC_InitStructure;
     
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
     
     RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
     
     GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//ADC
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;    //模拟输入
     GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitStructure);
     
     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式    
     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//禁止触发检测，使用软件触发
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐    
     ADC_InitStructure.ADC_NbrOfChannel = 1;//1个转换在规则序列中 也就是只转换规则序列1 
     ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
     
     ADC_Cmd(ADC1, ENABLE);//开启AD转换器
     
     ADC_ResetCalibration(ADC1);//重置指定的ADC的校准寄存器
     while(ADC_GetResetCalibrationStatus(ADC1));//获取ADC重置校准寄存器的状态
     
     ADC_StartCalibration(ADC1);//开始指定ADC的校准状态
     while(ADC_GetCalibrationStatus(ADC1));//获取指定ADC的校准程序
 
     ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
 }
 /*******************************************************************************
 * 函 数 名         : Get_ADC_Value
 * 函数功能           : 获取通道ch的转换值，取times次,然后平均     
 * 输    入         : ch:通道编号
                      times:获取次数
 * 输    出         : 通道ch的times次转换结果平均值
 *******************************************************************************/
 u16 Get_ADC_Value(u8 ch,u8 times)
 {
     u32 temp_val=0;
     u8 t;
     //设置指定ADC的规则组通道，一个序列，采样时间
     ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);    //ADC1,ADC通道,239.5个周期,提高采样时间可以提高精确度                
     
     for(t=0;t<times;t++)
     {
         ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的ADC1的软件转换启动功能    
         while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
         temp_val+=ADC_GetConversionValue(ADC1);
    }
     return temp_val/times;
 } 
  /*******************************************************************************
 * 函 数 名         : PVD掉电
 * 函数功能         : 掉电   中断
 * 输    入         : 
                      
 * 输    出         : 
 *******************************************************************************/
 
 void PVD_Init(void)
{

EXTI_InitTypeDef EXTI_InitStructure;

//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//PWR_PVDLevelConfig(PWR_PVDLevel_2V9); 
//PWR_PVDCmd(ENABLE);
	
EXTI_ClearITPendingBit(EXTI_Line16);
EXTI_InitStructure.EXTI_Line = EXTI_Line16;   // PVD连接到中断线16上  
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //使用中断模式 
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//表示电压从高电压下降到低于设定的电压阀值产生中断
EXTI_InitStructure.EXTI_LineCmd = ENABLE; // 使能中断线  
EXTI_Init(&EXTI_InitStructure);   //初始化
	
	PVD_NVIC();
}

void PVD_NVIC(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

/* Configure one bit for preemption priority */
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

/* Enable the PVD Interrupt */
NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
PWR_PVDLevelConfig(PWR_PVDLevel_2V9); 
PWR_PVDCmd(ENABLE);
}

