#ifndef __MPORT_H
#define __MPORT_H 
#include "sys.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32������
//MODBUS �ӿڲ���������	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/8/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2017-2027
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

 
void mp_init(u32 pclk2,u32 bound);			//��ʼ���ӿ�
void mp_send_data(u8* buf, u16 len);		//�������� 
void QingJiao_F(void);                      //��� ������

#endif

















