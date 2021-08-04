#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"


extern u8 canbuf_rxd[8];
	
 
//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    
										 							 				    
void CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
void Can_Send_Msg(u32 mid,u8* msg,u8 len);						//发送数据

u8 Can_Receive_Msg(u8 *buf);							//接收数据
#endif

















