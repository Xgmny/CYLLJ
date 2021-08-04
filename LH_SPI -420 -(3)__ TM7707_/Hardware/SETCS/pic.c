#include "oled.h"
#include "gui.h"
#include "pic.h"



void CAN_SET(void)
{
	u8 X=0;
	OLED_Clear(0); 
	do
	{
		GUI_ShowString(X,10,"*",1,16,1);
		X+=8;
	}
	while(X<128);
	GUI_ShowString(0,30,"*",1,16,1);
	GUI_ShowCHinese(16,30,16,"正在设置参数",1);
	GUI_ShowString(120,30,"*",1,16,1);
	X=0;
	do
	{
		GUI_ShowString(X,50,"*",1,16,1);
		X+=8;
	}
	while(X<128);
}	
void ONE(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(16,0,16,"向修正参数：",1);
	GUI_ShowCHinese(3,16,16,"零点：",1);
	GUI_ShowCHinese(3,32,16,"切除：",1);
	GUI_ShowString(96,16,"KPa",3,16,1);
//	GUI_ShowString(105,19,"3",1,8,1);
	GUI_ShowString(96,32,"m /h",4,16,1);
	GUI_ShowString(105,35,"3",1,8,1);
	GUI_ShowString(2,48,"<10%:",5,16,1);
	
}	
void TWO(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(16,0,16,"向修正参数：",1);
	GUI_ShowString(4,16,"10%~20%:",8,16,1);
	GUI_ShowString(4,32,"20%~30%:",8,16,1);
	GUI_ShowString(4,48,"30%~40%:",8,16,1);
	
}
void THERR(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(16,0,16,"向修正参数：",1);
	GUI_ShowString(4,16,"40%~50%:",8,16,1);
	GUI_ShowString(4,32,"50%~60%:",8,16,1);
	GUI_ShowString(4,48,"60%~70%:",8,16,1);
	
}
void FOUR(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(16,0,16,"向修正参数：",1);
	GUI_ShowString(4,16,"70%~80%:",8,16,1);
	GUI_ShowString(4,32,"80%~90%:",8,16,1);
	GUI_ShowString(4,48,"90%~100%:",9,16,1);
	
}
void MENU(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(10,0,16,"设置正向参数",1);
	GUI_ShowCHinese(10,16,16,"设置反向参数",1);
	GUI_ShowCHinese(10,32,16,"设置修正参数",1);
	GUI_ShowCHinese(10,48,16,"设置通讯地址",1);
	GUI_ShowChar(113,4,32,8,0);
}
void FIVE(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(21,16,16,"向流量量程：",1);
	GUI_ShowString(88,38,"m /h",4,16,1);
	GUI_ShowString(97,41,"3",1,8,1);
	
}
void SIX(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(0,0,16,"温度零点：",1);
	GUI_ShowCHinese(0,16,16,"温度系数：",1);
	GUI_ShowCHinese(16,32,16,"度以上：",1);
	GUI_ShowCHinese(16,48,16,"度以下：",1);
	GUI_ShowString(0,32,"25",2,16,1);
	//GUI_ShowString(32,32,"C",1,16,1);
	GUI_ShowString(0,48,"25",2,16,1);
	//GUI_ShowString(32,48,"C",1,16,1);
}
void SEV(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(21,15,16,"通讯地址：",1);
}
void QJHM(void)
{	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(0,0,16,"倾角",1);
	GUI_ShowCHinese(24,32,16,"度：",1);
	GUI_ShowString(0,32,"+30",3,16,1);
	GUI_ShowString(0,48,"-30",3,16,1);
	GUI_ShowCHinese(24,48,16,"度：",1);
}
void FIRST(void)
{
#if XS	
	OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(0,0,16,"流量",1);
	GUI_ShowCHinese(0,16,16,"累计",1);
	GUI_ShowCHinese(0,32,16,"流速",1);
	GUI_ShowCHinese(0,48,16,"差压",1);
	GUI_ShowString(100,0,"m/h",3,16,1);
	GUI_ShowString(108,3,"3",1,8,1);
	GUI_ShowString(112,19,"m",1,16,1);
	GUI_ShowString(120,19,"3",1,8,1);
	GUI_ShowString(104,32,"m/s",3,16,1);
	GUI_ShowString(104,48,"KPa",3,16,1);
	
#else
		OLED_Clear(0);             //清屏（全黑）
	GUI_ShowCHinese(0,3,16,"流量",1);
	GUI_ShowCHinese(0,24,16,"累计",1);
	GUI_ShowCHinese(0,45,16,"差压",1);
	GUI_ShowString(100,3,"m/h",3,16,1);
	GUI_ShowString(108,3,"3",1,8,1);
	GUI_ShowString(112,24,"m",1,16,1);
	GUI_ShowString(120,24,"3",1,8,1);
	GUI_ShowString(104,45,"KPa",3,16,1);
						
#endif	
}
void FIRST_2(void)
{	
		OLED_Clear(0);             //??(??)
GUI_DrawRectangle(0, 5, WIDTH/2-1, HEIGHT-1-22,1);
GUI_DrawRectangle(WIDTH/2-1,5,  WIDTH-1, HEIGHT-1-22,1);
	
	GUI_ShowCHinese(16,3,16,"温度",1);
	GUI_ShowCHinese(79,3,16,"温差",1);
	GUI_ShowCHinese(0,45,16,"角度",1);
	GUI_ShowString(46,20,"o",1,8,1);
	GUI_ShowString(52,21,"C",1,16,1);
	GUI_ShowString(107,21,"Pa",2,16,1);
	GUI_ShowString(102,42,"o",1,8,1);
}

