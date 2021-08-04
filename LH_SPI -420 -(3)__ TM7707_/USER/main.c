#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "24c64.h"	
#include "wdg.h"
#include "timer.h"
#include "usart.h"
#include "usmart.h"
#include "oled.h"
#include "setcs.h"
#include "can.h"
#include "gui.h"
#include "pic.h"
#include "CS1239.h"
#include "TM7707.h"
#include "mport.h"
#include "IIC__.h"



    u8 lwd[8]={0x2b,0x33,0x32,0x30,0x2e,0x30,0x32,0x30};
	u8 lwd_pa[8]={0x2b,0x33,0x32,0x30,0x2e,0x30,0x32,0x30};
	u8 lll[8]={0x2b,0x33,0x32,0x30,0x2e,0x30,0x32,0x30};
	u8 ljl[8]={0x2b,0x33,0x32,0x30,0x30,0x32,0x2e,0x30};
	u8 lsl[8]={0x2b,0x33,0x32,0x2e,0x30,0x32};
	u8 cyl[8]={0x2d,0x33,0x32,0x30,0x2e,0x30,0x32,0x30};
	u8 jdl[8]={0x2b,0x33,0x32,0x2e,0x30,0x32};
	
	int32_t LJ;
	int32_t LL;
	u16 A;
	u16 SZ_JZ_Z[10], SZ_JZ_F[10] ;                     //   %比校正
	u16 SZ_LD_Z, SZ_LD_F, SZ_QC_Z, SZ_QC_F;       //   0点    切除
	int32_t  SZ_LL_Z,SZ_LL_F;
	
   extern u32 NIAN;
   extern u8 key,se30,sec3,sec,ljks,slj3,slj30,have;
   extern u8 idata,date8[];
   extern u16 QJs;
   u8 rxd_bz,canbuf_rxd[8];
	
 int main(void)
 {	
	 
	u8 cnt=0,old_key=0,hmqh,run;
	u8 canbuf_txd[8]={0x00,0x00,0x32,0x30,0x30,0x30,0x2e,0x30};


	delay_init();	    	 //延时函数初始化	
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();				//按键初始化		
	AT24CXX_Init();			//IIC初始化 
	TM7707_init( );
	OLED_Init();
	FIRST(); ljks=1;hmqh=0;
	TIM4_init(1999,7199);//定时器4 200毫秒
//	WBZD_Init();

	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,8,0);//CAN初始,波特率250Kbps 
									//最后参数  mode:0,普通模式;1,回环模式; //  
//   IWDG_Init(4,6250);      //狗10s
	 run=1;      //运行
	LED0=1;        
 	while(1)
	{

		if (rxd_bz)//接收到有数据
		{
			if (canbuf_rxd[0]=='O')
			{
				if((canbuf_rxd[1]=='U')&(canbuf_rxd[2]=='T'))
				      {run=1;cnt=0;FIRST();}//运行
			}
			else
			{
				if (canbuf_rxd[0]=='$')
				{	
					if (canbuf_rxd[1]=='Y')
						{	run=2;	
							CAN_Answer();
						}
				}	
				else 
					CAN_SAVE();
			}
		}
		if (run<2)
		{
			if(ms200==1)			//200毫秒
			{
				LED0=!LED0;	
				key=KEY_Scan();
				if (key==4) 
					{
						if(have==0)
								{have=1;sec3=0;slj3=0;}
							else
							{
								if(sec3) 
								{
									sec3=0;have=0;
									if(run==1)
									{
										run=0;   SET_IN();   //设置
									}
									else 
									{
										BL_24c64();  //??????????
										run=1;  cnt=0; FIRST(); }
									}
							}			
						}		
				else
					{
						if (have)
							have=0;
						if(run==1)
							{
								if((key==0)&(old_key==3))
								{
									if (hmqh>=1)
										{	hmqh=0;FIRST();}
									else
											{hmqh=1;FIRST_2();}
								}else;
								if (!hmqh)	
								{	
									 GUI_ShowString(34, 3,lll,8,16,1); // 流量
						             GUI_ShowString(34,24,ljl,8,16,1);	
						             GUI_ShowString(34,45,cyl,8,16,1);	
								}
								else{
									GUI_ShowString(4, 21,lwd,5,16,1); 
			//						GUI_ShowNum(34,24,QJs,7,16,1); 
									GUI_ShowString(70,21,lwd_pa ,4,16,1);	//倾角	jdl				
									GUI_ShowString(34,45,jdl,8,16,1);	//
									}
							
							old_key=key;
									
							}
							else
								SET_COME();	//设置
						}
				  if (run==1)	
					{
						 Made_Data();		//AD转换	
						if (se30)			//=1累计使能  30秒
							LJLL_Data();
						cnt++;
						if (cnt>=255) cnt=0;
						canbuf_txd[0]=cnt;

						canbuf_txd[2]=LL>>8;
						canbuf_txd[3]=LL;
						canbuf_txd[4]=LJ>>24;
						canbuf_txd[5]=LJ>>16;
						canbuf_txd[6]=LJ>>8;
						canbuf_txd[7]=LJ;
						Can_Send_Msg(myid,canbuf_txd,8);//发送8个字节 
					}
				ms200=0;  
			}
		}	
		
	}
}
