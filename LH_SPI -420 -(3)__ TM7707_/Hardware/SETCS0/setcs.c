#include "key.h"
#include "timer.h"
#include "24c64.h"	
#include "gui.h"
#include "pic.h"
#include "setcs.h"
#include "can.h"
#include "delay.h"
extern u32 NIAN;
u32 myid;
void CAN_Answer(void)	
{
	u8 shu[8],Ctxd[8],rr;
	CAN_SET();
	AT24CXX_Read(0x01D0,shu,6);
	Ctxd[0]=0X5A;Ctxd[1]=0X53;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];Ctxd[7]=shu[5];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01D8,shu,6);
	Ctxd[0]=0X46;Ctxd[1]=0X53;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];Ctxd[7]=shu[5];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	rr=0;
	delay_ms(50);
	AT24CXX_Read(0x0110,shu,5);//L
	Ctxd[0]=0X5A;Ctxd[1]=0X4c;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];Ctxd[7]=0x20;
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0170,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X4c;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];Ctxd[7]=0x20;
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0118,shu,5);//Q
	Ctxd[0]=0X5A;Ctxd[1]=0X51;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0178,shu,6);
	Ctxd[0]=0X46;Ctxd[1]=0X51;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0120,shu,5);//0
	Ctxd[0]=0X5A;Ctxd[1]=0X30;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0180,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X30;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0128,shu,5);//1
	Ctxd[0]=0X5A;Ctxd[1]=0X31;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0188,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X31;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0130,shu,5);//2
	Ctxd[0]=0X5A;Ctxd[1]=0X32;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0190,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X32;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0138,shu,5);//3
	Ctxd[0]=0X5A;Ctxd[1]=0X33;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x0198,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X33;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0140,shu,5);//4
	Ctxd[0]=0X5A;Ctxd[1]=0X34;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01A0,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X34;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0148,shu,5);//5
	Ctxd[0]=0X5A;Ctxd[1]=0X35;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01A8,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X35;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0150,shu,5);//6
	Ctxd[0]=0X5A;Ctxd[1]=0X36;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01B0,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X36;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0158,shu,5);//7
	Ctxd[0]=0X5A;Ctxd[1]=0X37;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01B8,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X37;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0160,shu,5);//8
	Ctxd[0]=0X5A;Ctxd[1]=0X38;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01C0,shu,8);
	Ctxd[0]=0X46;Ctxd[1]=0X38;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);
	AT24CXX_Read(0x0168,shu,5);//9
	Ctxd[0]=0X5A;Ctxd[1]=0X39;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	delay_ms(50);			
	AT24CXX_Read(0x01C8,shu,5);
	Ctxd[0]=0X46;Ctxd[1]=0X39;Ctxd[2]=shu[0];Ctxd[3]=shu[1];
	Ctxd[4]=shu[2];Ctxd[5]=shu[3];Ctxd[6]=shu[4];
	rr=Can_Send_Msg(myid,Ctxd,8);//发送8个字节 
	
}
void CAN_SAVE(void)
{
	u8 n0,cc[8];
	for(n0=0;n0<6;n0++)	
		cc[n0]=canbuf_rxd[n0+2];
	if(canbuf_rxd[0]=='Z')
	{
		switch (canbuf_rxd[1])
		{
			case 'L':{AT24CXX_Write(0x0110,cc,5);}break;
			case 'Q':{AT24CXX_Write(0x0118,cc,5);}break;
			case '0':{AT24CXX_Write(0x0120,cc,5);}break;
			case '1':{AT24CXX_Write(0x0128,cc,5);}break;
			case '2':{AT24CXX_Write(0x0130,cc,5);}break;
			case '3':{AT24CXX_Write(0x0138,cc,5);}break;
			case '4':{AT24CXX_Write(0x0140,cc,5);}break;
			case '5':{AT24CXX_Write(0x0148,cc,5);}break;
			case '6':{AT24CXX_Write(0x0150,cc,5);}break;
			case '7':{AT24CXX_Write(0x0158,cc,5);}break;
			case '8':{AT24CXX_Write(0x0160,cc,5);}break;
			case '9':{AT24CXX_Write(0x0168,cc,5);}break;
			case 'S':{AT24CXX_Write(0x01D0,cc,5);}break;
			default:{};break;
		}
	}
	if(canbuf_rxd[0]=='F')
	{
		switch (canbuf_rxd[1])
		{
			case 'L':{AT24CXX_Write(0x0170,cc,5);}break;
			case 'Q':{AT24CXX_Write(0x0178,cc,5);}break;
			case '0':{AT24CXX_Write(0x0180,cc,5);}break;
			case '1':{AT24CXX_Write(0x0188,cc,5);}break;
			case '2':{AT24CXX_Write(0x0190,cc,5);}break;
			case '3':{AT24CXX_Write(0x0198,cc,5);}break;
			case '4':{AT24CXX_Write(0x01A0,cc,5);}break;
			case '5':{AT24CXX_Write(0x01A8,cc,5);}break;
			case '6':{AT24CXX_Write(0x01B0,cc,5);}break;
			case '7':{AT24CXX_Write(0x01B8,cc,5);}break;
			case '8':{AT24CXX_Write(0x01C0,cc,5);}break;
			case '9':{AT24CXX_Write(0x01C8,cc,5);}break;
			case 'S':{AT24CXX_Write(0x01D8,cc,5);}break;
			default:{};break;
		}
	}
	if(canbuf_rxd[0]=='L')
	{
		for(n0=0;n0<8;n0++)
			cc[n0]=0x30;
		cc[6]=0x2e;
		AT24CXX_Write(0x0200+NIAN,cc,8);}
}
void SET_IN(void)	
{
	page=0;MENU();row=113;col=4;smode=1;wz=0;
}

void SET_COME(void)	
{   
	static u8 tem,fx,xgbz,skey,lsk;
	static u16 addr;
	static u8 ss[7],ld[8],qc[5];
	//skey=KEY_Scan();
	skey=key;
	if(skey<4)
	{
		if(lsk==skey)
			{
				if (skey==3)
				skey=0;}
		else
			lsk=skey;
		if(skey==3)		//确定保存数据，翻页
		  {
			if (page==0)
			{
				switch (wz)
				{
					case 0x02:{	SIX();page=6;wz=0;row=15;smode=1;}break;
					case 0x03:{
								SEV();page=7;wz=0;
								AT24CXX_Read(0X0108,ld,2);
								GUI_ShowString(47,38,ld,2,16,1);
								row=47;col=38;smode=1;
								}break;
					case 0x00:	{
									ONE();page=1;xgbz=0;
									fx=0;	GUI_ShowCHinese(0,0,16,"正",1);	
									addr=0x0110;wz=0;
									AT24CXX_Read(addr,ss,5);
									addr+=8;
									AT24CXX_Read(addr,ld,5);
									addr+=8;
									AT24CXX_Read(addr,qc,5);
									GUI_ShowString(47,16,ss,5,16,1);
									GUI_ShowString(47,32,ld,5,16,1);
									GUI_ShowString(47,48,qc,5,16,1);
									col=16;row=47;tem=ss[wz];
								}break;
					case 0x01:	{
									ONE();page=1;xgbz=0;
									fx=1;GUI_ShowCHinese(0,0,16,"反",1);
									addr=0x0170;wz=0;
									AT24CXX_Read(addr,ss,5);
									addr+=8;
									AT24CXX_Read(addr,ld,5);
									addr+=8;
									AT24CXX_Read(addr,qc,5);
									GUI_ShowString(47,16,ss,5,16,1);
									GUI_ShowString(47,32,ld,5,16,1);
									GUI_ShowString(47,48,qc,5,16,1);
									col=16;row=47;tem=ss[wz];
								}break;
					}
			}
			else
			{
				if(page==6)
				{
					if (row==65)
					{
						
						ld[0]=0x30;ld[1]=0x30;ld[2]=0x30;ld[3]=0x30;
						ld[4]=0x30;ld[5]=0x30;ld[6]=0x2e;ld[7]=0x30;
						AT24CXX_Write(0x0200+NIAN,ld,8);
						
					}
					MENU();row=113;col=4;smode=0;wz=0;page=0;	
				}
				else
				{
					if (page==7)
						{
							if (xgbz==1)
							{
				                ss[wz]=tem;
								AT24CXX_Write(0x0104,ss,3);
								myid=A_N_24C64(3,ss,0x0104);
								myid=0x11940400+myid;
							}
							MENU();row=113;col=4;smode=0;wz=0;page=0;	
						}
					if (page==5)
						{
							if (xgbz==1)
							{
								ss[wz]=tem;
								if(fx==0) 
									addr=0x01D0;
									else 
										addr=0x01D8;
							AT24CXX_Write(addr,ss,6);
							}
							MENU();row=113;col=4;smode=0;wz=0;page=0;	
						}
					if ((page==1)|(page==2)|(page==3)|(page==4))
					{
						if (xgbz==1)
						{
							if(col==16) ss[wz]=tem;
							if(col==32) ld[wz]=tem;
							if(col==48) qc[wz]=tem;
							if (page==1)
								{if(fx==0) addr=0x0110;
									else addr=0x0170;}
							if (page==2)
								{if(fx==0) addr=0x0128;
									else addr=0x0188;}	
							if (page==3)
								{if(fx==0) addr=0x0140;
									else addr=0x01a0;}
							if (page==4)
								{if(fx==0) addr=0x0158;
									else addr=0x01b8;}	
							AT24CXX_Write(addr,ss,5);
							addr+=8;AT24CXX_Write(addr,ld,5);
							addr+=8;AT24CXX_Write(addr,qc,5);
						}
						page++;wz=0;
						if (page==5)
						{	
							FIVE();	
							if(fx==0) 
									addr=0x01D0;
							else 
									addr=0x01D8;
							if(fx==0)
									GUI_ShowCHinese(5,16,16,"正",1);	
							else
									GUI_ShowCHinese(5,16,16,"反",1);
							AT24CXX_Read(addr,ss,6);
							GUI_ShowString(24,38,ss,6,16,1);
							col=38;row=24;tem=ss[wz];xgbz=0;
							}
						else
						{
							if (page==2)
								{	TWO();
									if(fx==0) addr=0x0128;
									else addr=0x0188;}
							if (page==3)
								{	THERR();
									if(fx==0) addr=0x0140;
									else addr=0x01a0;}
							if (page==4)
								{	FOUR();	if(fx==0) addr=0x0158;
									else addr=0x01b8;}				
							if(fx==0)
									GUI_ShowCHinese(0,0,16,"正",1);	
							else
								GUI_ShowCHinese(0,0,16,"反",1);
							AT24CXX_Read(addr,ss,5);
							addr+=8;AT24CXX_Read(addr,ld,5);
							addr+=8;AT24CXX_Read(addr,qc,5);
							GUI_ShowString(80,16,ss,5,16,1);
							GUI_ShowString(80,32,ld,5,16,1);
							GUI_ShowString(80,48,qc,5,16,1);
							col=16;row=80;tem=ss[wz];xgbz=0;
						}
					}
				}	
			xgbz=0;
			}
		}
	if(skey==2)//右
		{
 			if (page==0) 
				{   GUI_ShowChar(113,col,32,8,1);
					col+=16;wz++;smode=0;
					if(col>64) {col=4;wz=0;}
					GUI_ShowChar(113,col,32,8,0);
				}
			 if ((page==1)|(page==2)|(page==3)|(page==4))
				{	GUI_ShowChar(row,col,tem,16,1);
					row+=8;wz++;smode=1;
					if(page==1)
					{
						if(col==48)
						{	if(row==55) {row+=8;wz++;}}
						else
							{	if(row==63) {row+=8;wz++;}}
						if (row>=87)
							{row=47;col+=16;wz=0;
							if(col>=64) col=16;}
						if (col==16) tem=ss[wz];
						if (col==32) tem=ld[wz];
						if (col==48) tem=qc[wz];
						GUI_ShowChar(row,col,tem,16,1);
					}						
					if ((page==2)|(page==3)|(page==4))
					{	
						if(row==88) {row+=8;wz++;}
						if (row>=120)
							{row=80;col+=16;wz=0;
							if(col>=64) col=16;}	
					}
					if (col==16) tem=ss[wz];
					if (col==32) tem=ld[wz];
					if (col==48) tem=qc[wz];
					GUI_ShowChar(row,col,tem,16,1);
				}	
			 if (page==5)
				{	GUI_ShowChar(row,col,tem,16,1);
					row+=8;wz++;smode=1;
					if(row==56) {row+=8;wz++;}
					tem=ss[wz];
					if (row>64)
							{row=24;wz=0;tem=ss[wz];}
					GUI_ShowChar(row,38,tem,16,1);
				}
			if (page==6)
				{
					if(row==15)
						{GUI_ShowCHinese(15,38,16,"保持",1);
							GUI_ShowCHinese(65,38,16,"清零",1);
							row=65;smode=1;}
					else
						{
							row=15;smode=1;
						 GUI_ShowCHinese(65,38,16,"清零",1);
							GUI_ShowCHinese(15,38,16,"保持",1);}
					 }
			if (page==7)
				{	GUI_ShowChar(row,col,tem,16,1);
					row+=8;wz++;smode=1;
					if(wz==3) {row=47;wz=0;}
					tem=ld[wz];
					GUI_ShowChar(row,38,tem,16,1);
				}	
		}
		if(skey==1)//+
		{
 			if(page==0)
			{	GUI_ShowChar(113,col,32,8,1);
					col+=16;wz++;smode=0;
					if(col>64) {col=4;wz=0;}
					GUI_ShowChar(113,col,32,8,0);
			}
			else
				{
					if (page==6)
					{
					if(row==65)
						{	
							GUI_ShowCHinese(65,38,16,"清零",1);
							row=15;smode=1;
							GUI_ShowCHinese(15,38,16,"保持",1);
						}
					else
						{
							row=65;smode=1;
							GUI_ShowCHinese(15,38,16,"保持",1);
							GUI_ShowCHinese(65,38,16,"清零",1);
							
						}
					 }	
					else
					{
						tem++;xgbz=1;
						if (tem>=0x3a) tem=0x30;smode=1;
						GUI_ShowChar(row,col,tem,16,1);
					}	
				}
		}
	}
	if (smode==1) 
			smode=0;
		else
			smode=1;
	if(page==0)
				GUI_ShowChar(113,col,32,8,smode);
			else
			{
				if(page==6)
				{
					if(row==65)
						GUI_ShowCHinese(65,38,16,"清零",smode);
					else
						 GUI_ShowCHinese(15,38,16,"保持",smode);
				}
				else	
					GUI_ShowChar(row,col,tem,16,smode);
			}
}	
	
	