#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"


extern u8 canbuf_rxd[8];
	
 
//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.								    
										 							 				    
void CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
void Can_Send_Msg(u32 mid,u8* msg,u8 len);						//��������

u8 Can_Receive_Msg(u8 *buf);							//��������
#endif
















