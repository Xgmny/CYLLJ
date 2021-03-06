#include "protocol.h"
#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//MODBUS 协议层驱动代码	  
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2017/8/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2017-2027
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


m_protocol_dev_typedef m_ctrl_dev;	//定义modbus控制器


//解析一帧数据，解析结果存储在fx里面
//注意：本函数会用到malloc给fx数据指针申请内存，后续用完fx，一定要释放内存！！
//否则会引起内存泄露！！！
//fx：帧指针 
//返回值：解析结果，0，OK，其他，错误代码。
m_result mb_unpack_frame(m_frame_typedef *fx)
{
 	u16 rxchkval=0;   	 		//接收到的校验值 
	u16 calchkval=0;			//计算得到的校验值	
 	u8 datalen=0; 				//有效数据长度 
	fx->datalen=0; 				//数据长度清零
	if(m_ctrl_dev.rxlen>M_MAX_FRAME_LENGTH||m_ctrl_dev.rxlen<M_MIN_FRAME_LENGTH)
	{
		m_ctrl_dev.rxlen=0;			//清除rxlen
		m_ctrl_dev.frameok=0;		//清除framok标记，以便下次可以正常接收 
		return MR_FRAME_FORMAT_ERR;//帧格式错误
	}
	datalen=m_ctrl_dev.rxbuf[3];
	switch(m_ctrl_dev.checkmode)
	{
		case M_FRAME_CHECK_SUM:							//校验和
			calchkval=mc_check_sum(m_ctrl_dev.rxbuf,datalen+4);
			rxchkval=m_ctrl_dev.rxbuf[datalen+4];
			break;
		case M_FRAME_CHECK_XOR:							//异或校验
			calchkval=mc_check_xor(m_ctrl_dev.rxbuf,datalen+4);
			rxchkval=m_ctrl_dev.rxbuf[datalen+4];
			break;
		case M_FRAME_CHECK_CRC8:						//CRC8校验
			calchkval=mc_check_crc8(m_ctrl_dev.rxbuf,datalen+4);
			rxchkval=m_ctrl_dev.rxbuf[datalen+4];
			break;
		case M_FRAME_CHECK_CRC16:						//CRC16校验
			calchkval=mc_check_crc16(m_ctrl_dev.rxbuf,datalen+4);
			rxchkval=((u16)m_ctrl_dev.rxbuf[datalen+4]<<8)+m_ctrl_dev.rxbuf[datalen+5];
			break;
	} 	
	m_ctrl_dev.rxlen=0;			//清除rxlen
	m_ctrl_dev.frameok=0;		//清除framok标记，以便下次可以正常接收 
	if(calchkval==rxchkval)		//校验正常
	{
		fx->address=m_ctrl_dev.rxbuf[0];
		fx->function=m_ctrl_dev.rxbuf[1];
		fx->count=m_ctrl_dev.rxbuf[2];
		fx->datalen=m_ctrl_dev.rxbuf[3];
		if(fx->datalen)
		{
			fx->data=mymalloc(SRAMIN,fx->datalen);		//申请内存
			for(datalen=0;datalen<fx->datalen;datalen++)
			{
				fx->data[datalen]=m_ctrl_dev.rxbuf[4+datalen];		//拷贝数据
			}
		}
		fx->chkval=rxchkval;	//记录校验值		
	}else return MR_FRAME_CHECK_ERR;
	return MR_OK;	
}


//打包一帧数据，并发送 
//fx：指向需要打包的帧  
void mb_packsend_frame(m_frame_typedef *fx)
{  
	u16 i;
	u16 calchkval=0;			//计算得到的校验值	
	u16 framelen=0;				//打包后的帧长度
	u8 *sendbuf;				//发送缓冲区
	
	if(m_ctrl_dev.checkmode==M_FRAME_CHECK_CRC16)framelen=6+fx->datalen;
	else framelen=5+fx->datalen;
	sendbuf=mymalloc(SRAMIN,framelen);	//申请内存
	sendbuf[0]=fx->address;
	sendbuf[1]=fx->function;
	sendbuf[2]=fx->count;
	sendbuf[3]=fx->datalen; 
	for(i=0;i<fx->datalen;i++)
	{
		sendbuf[4+i]=fx->data[i];
	}	
	switch(m_ctrl_dev.checkmode)
	{
		case M_FRAME_CHECK_SUM:							//校验和
			calchkval=mc_check_sum(sendbuf,fx->datalen+4); 
			break;
		case M_FRAME_CHECK_XOR:							//异或校验
			calchkval=mc_check_xor(sendbuf,fx->datalen+4); 
			break;
		case M_FRAME_CHECK_CRC8:						//CRC8校验
			calchkval=mc_check_crc8(sendbuf,fx->datalen+4); 
			break;
		case M_FRAME_CHECK_CRC16:						//CRC16校验
			calchkval=mc_check_crc16(sendbuf,fx->datalen+4); 
			break;
	} 
	
	if(m_ctrl_dev.checkmode==M_FRAME_CHECK_CRC16)		//如果是CRC16,则有2个字节的CRC
	{
		sendbuf[4+fx->datalen]=(calchkval>>8)&0XFF; 	//高字节在前
		sendbuf[5+fx->datalen]=calchkval&0XFF;			//低字节在后
	}else sendbuf[4+fx->datalen]=calchkval&0XFF;
	mp_send_data(sendbuf,framelen);	//发送这一帧数据
	myfree(SRAMIN,sendbuf);			//释放内存
}


//打包一帧数据，并发送 
//fx：指向需要打包的帧  
void mb_mod(m_modbus_typedef  *fx)
{  
	u16 i;
	u16 calchkval=0;			//计算得到的校验值	
	u16 framelen=0;				//打包后的帧长度
	u8 sendbuf[8];				//发送缓冲区
	



	sendbuf[0]=fx->m_1;
	sendbuf[1]=fx->m_2;
	sendbuf[2]=fx->m_3;
	sendbuf[3]=fx->m_4;
	sendbuf[4]=fx->m_5;
	sendbuf[5]=fx->m_6;
	
	calchkval=mc_check_crc16(sendbuf,6); 

//	sendbuf[6]=(calchkval>>8)&0XFF; 	//高字节在前
//	sendbuf[7]=calchkval&0XFF;			//低字节在后

	mp_send_data(sendbuf,6);	//发送这一帧数据

}

//初始化modbus
//checkmode：校验模式：0,校验和;1,异或;2,CRC8;3,CRC16
//返回值：0,成功;其他,错误代码
m_result mb_init(u8 checkmode)
{
	m_ctrl_dev.rxbuf=mymalloc(SRAMIN,M_MAX_FRAME_LENGTH);	//申请最大的帧接收缓存
	m_ctrl_dev.rxlen=0;
	m_ctrl_dev.frameok=0;
	m_ctrl_dev.checkmode=checkmode;
	if(m_ctrl_dev.rxbuf)return MR_OK;
	else return MR_MEMORY_ERR;
}

//结束MODBUS,释放内存
void mb_destroy(void)
{
	myfree(SRAMIN,m_ctrl_dev.rxbuf);	//申请最大的帧接收缓存
	m_ctrl_dev.rxlen=0;
	m_ctrl_dev.frameok=0; 
}




