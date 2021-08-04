//****************************************************************************************************/	
#include "oled.h"
#include "string.h"
#include "oledfont.h" 
#include "delay.h"
#include "gui.h"
#include <math.h>
#define FZX  0    //消除 
#define ZFX  0    //消除
#define FZ (SZ_QC_F*10)     //消除 
#define ZF (SZ_QC_Z*10)     //消除

//#define YuanMa (8388607-4113000)   //80Kp    无二极管5050000   有二极管 3617000   TM7707 3717000

//#define YuanMa (8388607-3015000)//7707 5v 单极
//#define YuanMa (13070000-8388607)//7707 5v 双极
#define YuanMa   (13627000-8388607)//7707 5v 双极

    static int32_t LJI;   //0.1<累计 累加变量
		   u8 BFB;        //校正
	extern u8 lwd[];
	extern u8 lll[];
	extern u8 ljl[];
	extern u8 lsl[];
	extern u8 cyl[];
	extern u8 jdl[];
	extern int32_t LJ;
	extern int32_t LL;
	extern u8 B,B1;
	extern u16 QJs;

	extern u16 SZ_JZ_Z[], SZ_JZ_F[];                     //   %比校正
	extern u16 SZ_LD_Z, SZ_LD_F, SZ_QC_Z, SZ_QC_F;       //   0点    切除
	extern int32_t  SZ_LL_Z,SZ_LL_F;		
           int32_t WD;	
	static int32_t WD_1;
	static int32_t  PJ[10];
	
	u32 WinDu[51]=
{
    0,
  398,  781, 1172, 1562, 1953, 2343, 2733, 3123, 3513, 3903,//10
 4292, 4682, 5071, 5460, 5850, 6239, 6627, 7016, 7405, 7794,//20
 8182, 8570, 8959, 9347, 9735,10123,10510,10899,11286,11673,//30
12060,12447,12835,13222,13608,13995,14382,14768,15155,15541,//40
15927,16313,16699,17085,17470,17856,18241,18627,19012,19397,//50
};

/*******************************************************************
 * @name       :void GUI_DrawPoint(u8 x,u8 y,u8 color)
 * @date       :2018-08-27
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
								color:the color value of the point
								      1-white
											0-black
 * @retvalue   :None
********************************************************************/
void GUI_DrawPoint(u8 x,u8 y,u8 color)
{
	OLED_Set_Pixel(x,y,color);
	OLED_Display();
}

/*******************************************************************
 * @name       :void GUI_Fill(u8 sx,u8 sy,u8 ex,u8 ey,u8 color)
 * @date       :2018-08-27 
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
                sy:the bebinning y coordinate of the specified area
								ex:the ending x coordinate of the specified area
								ey:the ending y coordinate of the specified area
								color:the color value of the the specified area
								      1-white
											0-black
 * @retvalue   :None
********************************************************************/
void GUI_Fill(u8 sx,u8 sy,u8 ex,u8 ey,u8 color)
{  	
	u8 i,j;			
	u8 width=ex-sx+1; 		//得到填充的宽度
	u8 height=ey-sy+1;		//高度
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
				OLED_Set_Pixel(sx+j, sy+i,color);
		}		
	}
	OLED_Display();
}

/*******************************************************************
 * @name       :void GUI_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
 * @date       :2018-08-27 
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
                y1:the bebinning y coordinate of the line
								x2:the ending x coordinate of the line
								y2:the ending y coordinate of the line
								color:the color value of the line
								      1-white
											0-black
 * @retvalue   :None
********************************************************************/
void GUI_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{ 
		OLED_Set_Pixel(uRow,uCol,color);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
	OLED_Display();
} 

/*****************************************************************************
 * @name       :void GUI_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
 * @date       :2018-08-27 
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
                y1:the bebinning y coordinate of the rectangle
								x2:the ending x coordinate of the rectangle
								y2:the ending y coordinate of the rectangle
								color:the color value of the rectangle
								      1-white
											0-black							  
 * @retvalue   :None
******************************************************************************/
void GUI_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
{
	GUI_DrawLine(x1,y1,x2,y1,color);
	GUI_DrawLine(x1,y1,x1,y2,color);
	GUI_DrawLine(x1,y2,x2,y2,color);
	GUI_DrawLine(x2,y1,x2,y2,color);
}  

/*****************************************************************************
 * @name       :void GUI_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
 * @date       :2018-08-27
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
                y1:the bebinning y coordinate of the filled rectangle
								x2:the ending x coordinate of the filled rectangle
								y2:the ending y coordinate of the filled rectangle
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/  
void GUI_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2,u8 color)
{
	GUI_Fill(x1,y1,x2,y2,color);
}
 
/*****************************************************************************
 * @name       :static void _draw_circle_8(u8 xc, u8 yc, u8 x, u8 y, u8 color)
 * @date       :2018-08-27 
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
								x:the x coordinate relative to the Circular center 
								y:the y coordinate relative to the Circular center 
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/  
static void _draw_circle_8(u8 xc, u8 yc, u8 x, u8 y, u8 color)
{
	OLED_Set_Pixel(xc + x, yc + y, color);
	OLED_Set_Pixel(xc - x, yc + y, color);
	OLED_Set_Pixel(xc + x, yc - y, color);
	OLED_Set_Pixel(xc - x, yc - y, color);
	OLED_Set_Pixel(xc + y, yc + x, color);
	OLED_Set_Pixel(xc - y, yc + x, color);
	OLED_Set_Pixel(xc + y, yc - x, color);
	OLED_Set_Pixel(xc - y, yc - x, color);
}

/*****************************************************************************
 * @name       :void GUI_DrawCircle(u8 xc, u8 yc, u8 color, u8 r)
 * @date       :2018-08-27
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
								r:Circular radius
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/  
void GUI_DrawCircle(u8 xc, u8 yc, u8 color, u8 r)
{
	int x = 0, y = r,d;
	d = 3 - 2 * r;
	while (x <= y) 
	{
		_draw_circle_8(xc, yc, x, y, color);
		if (d < 0) 
		{
				d = d + 4 * x + 6;
		}
		else 
		{
				d = d + 4 * (x - y) + 10;
				y--;
		}
		x++;
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_FillCircle(u8 xc, u8 yc, u8 color, u8 r)
 * @date       :2018-08-27
 * @function   :Fill a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
								r:Circular radius
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/  
void GUI_FillCircle(u8 xc, u8 yc, u8 color, u8 r)
{
	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;
	while (x <= y) 
	{
			for (yi = x; yi <= y; yi++)
			{
				_draw_circle_8(xc, yc, x, yi, color);
			}
			if (d < 0) 
			{
				d = d + 4 * x + 6;
			} 
			else 
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
	}
	OLED_Display();
}

/**********************************************************************************
 * @name       :void GUI_DrawTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
 * @date       :2018-08-27 
 * @function   :Draw a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge 
								y2:the ending y coordinate of the triangular edge 
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
***********************************************************************************/ 
void GUI_DrawTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
{
	GUI_DrawLine(x0,y0,x1,y1,color);
	GUI_DrawLine(x1,y1,x2,y2,color);
	GUI_DrawLine(x2,y2,x0,y0,color);
}

/*****************************************************************************
 * @name       :static void _swap(u8 *a, u8 *b)
 * @date       :2018-08-27
 * @function   :Exchange two numbers(internal call)
 * @parameters :a:the address of the first number 
                b:the address of the second number
 * @retvalue   :None
******************************************************************************/  
static void _swap(u8 *a, u8 *b)
{
	u16 tmp;
  tmp = *a;
	*a = *b;
	*b = tmp;
}

/*****************************************************************************
 * @name       :static void _draw_h_line(u8 x0,u8 x1,u8 y,u8 color)
 * @date       :2018-08-27
 * @function   :draw a horizontal line in RAM(internal call)
 * @parameters :x0:the bebinning x coordinate of the horizontal line
                x1:the ending x coordinate of the horizontal line
								y:the y coordinate of the horizontal line
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/
static void _draw_h_line(u8 x0,u8 x1,u8 y,u8 color)
{
	u8 i=0;
	for(i=x0;i<=x1;i++)
	{
		OLED_Set_Pixel(i, y, color);
	}
}

/*****************************************************************************
 * @name       :void GUI_FillTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
 * @date       :2018-08-27 
 * @function   :filling a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge 
								y2:the ending y coordinate of the triangular edge 
								color:the color value of the rectangle
								      1-white
											0-black	
 * @retvalue   :None
******************************************************************************/ 
void GUI_FillTriangel(u8 x0,u8 y0,u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
{
	u8 a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
 	}
 	if (y1 > y2) 
	{
    _swap(&y2,&y1); 
		_swap(&x2,&x1);
 	}
  if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
  }
	if(y0 == y2) 
	{ 
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		_draw_h_line(a,b,y0,color);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	
	if(y1 == y2)
	{
		last = y1; 
	}
  else
	{
		last = y1-1; 
	}
	for(y=y0; y<=last; y++) 
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			_swap(&a,&b);
		}
		_draw_h_line(a,b,y,color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			_swap(&a,&b);
		}
		_draw_h_line(a,b,y,color);
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
								chr:the ascii code of display character(0~94)
								Char_Size:the size of display character(8,16)
								mode:0-white background and black character
								     1-black background and white character
x:字符显示位置的起始x坐标
y:字符显示位置的初始y坐标
chr:显示字符(0~94)的ascii码
Char_Size:显示字符(8,16)的大小
模式:0-白色背景和黑色字符
黑色背景和白色角色
 * @retvalue   :None
******************************************************************************/ 
void GUI_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode)
{      	
	  unsigned char c=0,i=0,tmp,j=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>WIDTH-1){x=0;y=y+2;}
		if(Char_Size ==16)
		{
			for(i=0;i<16;i++)
			{
			  if(mode)
				{
					tmp = F8X16[c*16+i];  //
				}
				else
				{
					tmp = ~(F8X16[c*16+i]);
				}
				for(j=0;j<8;j++)
				{
					if(tmp&(0x80>>j))
					{
						OLED_Set_Pixel(x+j, y+i,1);
					}
					else
					{
						OLED_Set_Pixel(x+j, y+i,0);
					}
				}
			}
		}
		else if(Char_Size==8)
		{	
				for(i=0;i<8;i++)
				{
				  if(mode)
					{
						tmp = F6x8[c][i];
					}
					else
					{
						tmp = ~(F6x8[c][i]);
					}
					for(j=0;j<8;j++)
					{
						if(tmp&(0x80>>j))
						{
							OLED_Set_Pixel(x+j, y+i,1);
						}
						else
						{
							OLED_Set_Pixel(x+j, y+i,0);
						}
					}
			}
	}
		else if(Char_Size==24)
		{	
					for(i=0;i<24;i++)
				{
				  if(mode)
					{
						tmp = F8X24[24*c+i];
					}
					else
					{
						tmp = ~(F8X24[24*c+i]);
					}
					for(j=0;j<8;j++)
					{
						if(tmp&(0x80>>j))
						{
							OLED_Set_Pixel(x+j, y+i,1);
						}
						else
						{
							OLED_Set_Pixel(x+j, y+i,0);
						}
					}
			}
	}
		else if(Char_Size==32)
		{	
					for(i=0;i<48;i++)
				{
				  if(mode)
					{
						tmp = F8X32[48*c+i];
					}
					else
					{
						tmp = ~(F8X32[48*c+i]);
					}
					for(j=0;j<8;j++)
					{
						if(tmp&(0x80>>j))
						{
							OLED_Set_Pixel(x+j+8, y+i/2,1);
						}
						else
						{
							OLED_Set_Pixel(x+j, y+i,0);
						}
					}
			}
	}		
	else
	{
		return;
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 mode) 反色
 * @date       :2018-08-27 
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
								chr:the start address of the English string
								Char_Size:the size of display character
								mode:0-white background and black character
								     1-black background and white character
 * @retvalue   :None
******************************************************************************/   	  
void GUI_ShowString_0(u8 x,u8 y,unsigned char *chr ,u8 Char_Size,u8 mode)
{
	unsigned char j=0,csize;
	if(Char_Size == 16)
  {
	  csize = Char_Size/2;
	}
  else if(Char_Size == 8)
  {
	  csize = Char_Size/2+2;
	}
	else
	{
		return;
	}
	while (chr[j]!='\0')
	{		
		GUI_ShowChar(x,y,chr[j],Char_Size,mode);
		x+=csize;
		if(x>120)
		{
			x=0;
			y+=Char_Size;
		}
		j++;
	}
}
//*****************************************************************************
void GUI_ShowString(u8 x,u8 y,unsigned char *chr,u8 len,u8 Char_Size,u8 mode)
{
	unsigned char j=0,csize;
	if(Char_Size == 16)
  {
	  csize = Char_Size/2;
	}
  else if(Char_Size == 8)
  {
	  csize = Char_Size/2+2;
	}
    else if(Char_Size == 24)
  {
	  csize = Char_Size/2-2;
	}
      else if(Char_Size == 32)
  {
	  csize = Char_Size/2-4;
	}
	else
	{
		return;
	}
	for (j=0;j<len;j++)
	{		
		GUI_ShowChar(x,y,chr[j],Char_Size,mode);
		x+=csize;
		if(x>120)
		{
			x=0;
			y+=Char_Size;
		}
	}
}
/*****************************************************************************
 * @name       :u32 mypow(u8 m,u8 n)
 * @date       :2018-08-27 
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/ 
static u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}



/*****************************************************************************
 * @name       :void GUI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 Size,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
								num:the number(0~4294967295)
								len:the length of the display number
								Size:the size of display number
								mode:0-white background and black character
								     1-black background and white character
* @parameters:  x:数字的初始x坐标
				y:数字的初始y坐标
				num: (0 ~ 4294967295)
				len:显示号的长度
				尺寸:显示数量的大小
				模式:0-白色背景和黑色字符
				黑色背景和白色角色
 * @retvalue   :None
******************************************************************************/  			 
void GUI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 Size,u8 mode)
{   	
	u8 t,temp;
	u8 enshow=0,csize;
/********************************************************************************/
	if(num&0x800000){
	num|=0xff000000;  //24位负  变32位负
	GUI_ShowChar(x-10,y,'-',Size,mode);//改过 -1
    num=~num+1;
	}
	else;
	
/********************************************************************************/	
	
  if(Size == 16)
  {
	  csize = Size/2;  //8
	}
  else if(Size == 8)
  {
	  csize = Size/2+2;  //6
	} 	
	else
	{
		return;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			
			if(temp==0&&t<2)      //0写空格
			{
				
				GUI_ShowChar(x+csize*(t),y,' ',Size,mode);//改过 -1
				continue;
			} 
			else{	enshow=1;
	        }
			
		}
//*************************************************************************
//	if(t<3)	          //加小数点
//	    GUI_ShowChar(x+csize*t,y,temp+'0',Size,mode); //'0'   ASCLL码
//	else if(t==3){
//		GUI_ShowChar(x+csize*t,y,'.',Size,mode); //优化
//	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);
//	}
//	else 
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);	
//*************************************************************************     
	}
} 

/********************************************************************************/
/********************************************************************************/
void GUI_ShowNum_LJ(u8 x,u8 y,int32_t num,u8 len,u8 Size,u8 mode)
{   	
	u8 t,temp;
	u8 enshow=0,csize;
/********************************************************************************/
	if(num&0x800000) num|=0xff000000;  //24位负  变32位负
		num=YS_LJ(num);
	if(num &0x80000000)
	   {  //32位数判断	
		num= ((~num)+1); //负数转换正数
		GUI_ShowChar(x-10,y,'-',Size,mode);//改过 -1
	   }
	else GUI_ShowChar(x-10,y,' ',Size,mode);//改过 
/********************************************************************************/
	
  if(Size == 16)
  {
	  csize = Size/2;  //8
	}
  else if(Size == 8)
  {
	  csize = Size/2+2;  //6
	} 	
	else
	{
		return;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			
			if(temp==0&&t<2)      //0写空格
			{
				
				GUI_ShowChar(x+csize*(t),y,' ',Size,mode);//改过 -1
				continue;
			} 
			else{	enshow=1;
	        }
			
		}
//*************************************************************************
	if(t<3)	          //加小数点
	    GUI_ShowChar(x+csize*t,y,temp+'0',Size,mode); //'0'   ASCLL码
	else if(t==3){
		GUI_ShowChar(x+csize*t,y,'.',Size,mode); //优化
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);
	}
	else 
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);	
//*************************************************************************     
	}
} 



/********************************************************************************/
/********************************************************************************/
void GUI_ShowNum_CY(u8 x,u8 y,int32_t num,u8 len,u8 Size,u8 mode)
{   	
	u8 t,temp;
	u8 enshow=0,csize;
/********************************************************************************/
	if(num&0x800000) num|=0xff000000;  //24位负  变32位负
		num=YS_CY(num);
	if(num &0x80000000)
	   {  //32位数判断	
		num= ((~num)+1); //负数转换正数
		GUI_ShowChar(x-10,y,'-',Size,mode);//改过 -1
	   }
	else GUI_ShowChar(x-10,y,' ',Size,mode);//改过 
/********************************************************************************/
	
  if(Size == 16)
  {
	  csize = Size/2;  //8
	}
  else if(Size == 8)
  {
	  csize = Size/2+2;  //6
	} 	
	else
	{
		return;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			
			if(temp==0&&t<2)      //0写空格
			{
				
				GUI_ShowChar(x+csize*(t),y,' ',Size,mode);//改过 -1
				continue;
			} 
			else{	enshow=1;
	        }
			
		}
//*************************************************************************
	if(t<3)	          //加小数点
	    GUI_ShowChar(x+csize*t,y,temp+'0',Size,mode); //'0'   ASCLL码
	else if(t==3){
		GUI_ShowChar(x+csize*t,y,'.',Size,mode); //优化
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);
	}
	else 
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);	
//*************************************************************************     
	}
} 



/********************************************************************************/
/********************************************************************************/
void GUI_ShowNum_LL(u8 x,u8 y,int32_t num,u8 len,u8 Size,u8 mode)
{   	
	u8 t,temp;
	u8 enshow=0,csize;
/********************************************************************************/
	if(num&0x800000) num|=0xff000000;  //24位负  变32位负
		num=YS_LL(num);
	if(num &0x80000000)
	   {  //32位数判断	
		num= ((~num)+1); //负数转换正数
		GUI_ShowChar(x-10,y,'-',Size,mode);//改过 -1
	   }
	else GUI_ShowChar(x-10,y,' ',Size,mode);//改过 
/********************************************************************************/	
	
  if(Size == 16)
  {
	  csize = Size/2;  //8
	}
  else if(Size == 8)
  {
	  csize = Size/2+2;  //6
	} 	
	else
	{
		return;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			
			if(temp==0&&t<2)      //0写空格
			{
				
				GUI_ShowChar(x+csize*(t),y,' ',Size,mode);//改过 -1
				continue;
			} 
			else{	enshow=1;
	        }
			
		}
//*************************************************************************
	if(t<3)	          //加小数点
	    GUI_ShowChar(x+csize*t,y,temp+'0',Size,mode); //'0'   ASCLL码
	else if(t==3){
		GUI_ShowChar(x+csize*t,y,'.',Size,mode); //优化
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);
	}
	else 
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);	
//*************************************************************************     
	}
} 



/********************************************************************************/
/********************************************************************************/
void GUI_ShowNum_WD(u8 x,u8 y,int32_t num,u8 len,u8 Size,u8 mode)
{   	
	u8 t,temp;
	u8 enshow=0,csize;
/********************************************************************************/
	if(num&0x800000) num|=0xff000000;  //24位负  变32位负
		num=YS_WD(num);
	if(num &0x80000000)
	   {  //32位数判断	
		num= ((~num)+1); //负数转换正数
		GUI_ShowChar(x-10,y,'-',Size,mode);//改过 -1
	   }
	else GUI_ShowChar(x-10,y,' ',Size,mode);//改过 
/********************************************************************************/	
	
  if(Size == 16)
  {
	  csize = Size/2;  //8
	}
  else if(Size == 8)
  {
	  csize = Size/2+2;  //6
	} 	
	else
	{
		return;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			
			if(temp==0&&t<2)      //0写空格
			{
				
				GUI_ShowChar(x+csize*(t),y,' ',Size,mode);//改过 -1
				continue;
			} 
			else{	enshow=1;
	        }
			
		}
//*************************************************************************
	if(t<3)	          //加小数点
	    GUI_ShowChar(x+csize*t,y,temp+'0',Size,mode); //'0'   ASCLL码
	else if(t==3){
		GUI_ShowChar(x+csize*t,y,'.',Size,mode); //优化
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);
	}
	else 
	    GUI_ShowChar(x+csize*(t+1),y,temp+'0',Size,mode);	
//*************************************************************************     
	}
}
/*****************************************************************************
 * @name       :void GUI_ShowFont16(u8 x,u8 y,u8 *s,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								s:the start address of the Chinese character
								mode:0-white background and black character
								     1-black background and white character
 * @retvalue   :None
******************************************************************************/ 
void GUI_ShowFont16(u8 x,u8 y,u8 *s,u8 mode)
{
	u8 i,j,k,tmp;
	u16 num;
	num = sizeof(cfont16)/sizeof(typFNT_GB16);
  for(i=0;i<num;i++)
	{
		if((cfont16[i].Index[0]==*s)&&(cfont16[i].Index[1]==*(s+1)))
		{
			for(j=0;j<32;j++)
			{
				if(mode)
				{
					tmp = cfont16[i].Msk[j];
				}
				else
				{
					tmp = ~(cfont16[i].Msk[j]);
				}
				for(k=0;k<8;k++)
				{
					if(tmp&(0x80>>k))
					{
						OLED_Set_Pixel(x+(j%2)*8+k, y+j/2,1);
					}
					else
					{
						OLED_Set_Pixel(x+(j%2)*8+k, y+j/2,0);
					}
				}
			}	
			break;
		}	
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_ShowFont24(u8 x,u8 y,u8 *s,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display a single 24x24 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								s:the start address of the Chinese character
								mode:0-white background and black character
								     1-black background and white character
 * @retvalue   :None
******************************************************************************/ 
void GUI_ShowFont24(u8 x,u8 y,u8 *s,u8 mode)
{
	u8 i,j,k,tmp;
	u16 num;
	num = sizeof(cfont24)/sizeof(typFNT_GB24);
  for(i=0;i<num;i++)
	{
		if((cfont24[i].Index[0]==*s)&&(cfont24[i].Index[1]==*(s+1)))
		{
			for(j=0;j<72;j++)
			{
				if(mode)
				{
					tmp = cfont24[i].Msk[j];
				}
				else
				{
					tmp = ~(cfont24[i].Msk[j]);
				}
				for(k=0;k<8;k++)
				{
					if(tmp&(0x80>>k))
					{
						OLED_Set_Pixel(x+(j%3)*8+k, y+j/3,1);
					}
					else
					{
						OLED_Set_Pixel(x+(j%3)*8+k, y+j/3,0);
					}
				}
			}	
			break;
		}	
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_ShowFont32(u8 x,u8 y,u8 *s,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display a single 32x32 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								s:the start address of the Chinese character
								mode:0-white background and black character
								     1-black background and white character
 * @retvalue   :None
******************************************************************************/ 
void GUI_ShowFont32(u8 x,u8 y,u8 *s,u8 mode)
{
	u8 i,j,k,tmp;
	u16 num;
	num = sizeof(cfont32)/sizeof(typFNT_GB32);
  for(i=0;i<num;i++)
	{
		if((cfont32[i].Index[0]==*s)&&(cfont32[i].Index[1]==*(s+1)))
		{
			for(j=0;j<128;j++)
			{
				if(mode)
				{
					tmp = cfont32[i].Msk[j];
				}
				else
				{
					tmp = ~(cfont32[i].Msk[j]);
				}
				for(k=0;k<8;k++)
				{
					if(tmp&(0x80>>k))
					{
						OLED_Set_Pixel(x+(j%4)*8+k, y+j/4,1);
					}
					else
					{
						OLED_Set_Pixel(x+(j%4)*8+k, y+j/4,0);
					}
				}
			}	
			break;
		}	
	}
	OLED_Display();
}

/*****************************************************************************
 * @name       :void GUI_ShowCHinese(u8 x,u8 y,u8 hsize,u8 *str,u8 mode)
 * @date       :2018-08-27 
 * @function   :Display Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese strings
                y:the bebinning y coordinate of the Chinese strings
								size:the size of Chinese strings
								str:the start address of the Chinese strings
								mode:0-white background and black character
								     1-black background and white character
 * @retvalue   :None
******************************************************************************/	   		   
void GUI_ShowCHinese(u8 x,u8 y,u8 hsize,u8 *str,u8 mode)
{ 
	while(*str!='\0')
	{
		if(hsize == 16)
		{
			GUI_ShowFont16(x,y,str,mode);
		}
		else if(hsize == 24)
		{
			GUI_ShowFont24(x,y,str,mode);
		}
		else if(hsize == 32)
		{
			GUI_ShowFont32(x,y,str,mode);
		}
		else
		{
			return;
		}
		x+=hsize;
		if(x>WIDTH-hsize)
		{
			x=0;
			y+=hsize;
		}
		str+=2;
	}			
}

/*****************************************************************************
 * @name       :void GUI_DrawBMP(u8 x,u8 y,u8 width, u8 height, u8 BMP[], u8 mode)
 * @date       :2018-08-27 
 * @function   :Display a BMP monochromatic picture
 * @parameters :x:the bebinning x coordinate of the BMP monochromatic picture
                y:the bebinning y coordinate of the BMP monochromatic picture
								width:the width of BMP monochromatic picture
								height:the height of BMP monochromatic picture
								BMP:the start address of BMP monochromatic picture array
								mode:0-white background and black character
								     1-black background and white character
x: BMP单色图的起始x坐标
y: BMP单色图的起始y坐标
宽度:BMP单色图片的宽度
高度:BMP单色图片的高度
BMP: BMP单色图像数组的起始地址
模式:0-白色背景和黑色字符
黑色背景和白色角色
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawBMP(u8 x,u8 y,u8 width, u8 height, u8 BMP[], u8 mode)
{ 	
 u8 i,j,k;
 u8 tmp;
 for(i=0;i<height;i++)
 {
		for(j=0;j<(width+7)/8;j++)
		{
		    if(mode)
				{
					tmp = BMP[i*((width+7)/8)+j];
				}
				else
				{
					tmp = ~BMP[i*((width+7)/8)+j];
				}
				for(k=0;k<8;k++)
				{
					if(tmp&(0x80>>k))
					{
						OLED_Set_Pixel(x+j*8+k, y+i,1);
					}
					else
					{
						OLED_Set_Pixel(x+j*8+k, y+i,0);
					}
				}
		}
 } 
 OLED_Display();
}
//***********************************************

//****************************************************
int32_t YS_LL(int32_t num){
  double i;
  
	//SZ_LL_Z=200;
	
	
 if(num>=ZF)	
	{
		 i=num;
		 i=SZ_LL_Z*10*(sqrt((i-ZFX)/(YuanMa-ZFX)));  //流量计算 5063000
		 num=(i+SZ_LD_Z*10)*SZ_JZ_Z[BFB]/1000;				  //零点  百分比校正 
//		 num=(i+SZ_LD_Z*10)*1/1000;				  //零点  百分比校正 
	}
 else if(num<(~FZ+2))
	{
		 i=~num+1;
		 i=SZ_LL_Z*10*(sqrt((i-FZX)/(YuanMa-FZX)));  //流量计算
	     num=(i+SZ_LD_F*10)*SZ_JZ_F[BFB]/1000;
//		 num=(i+SZ_LD_F*10)*1/1000;
		 num=~num+1;
	}
 else num=0;
	LL=num;
return num;
}
//****************************************************
int32_t YS_CY(int32_t num){
  double i;
	
	if((num>=ZFX))
	{
	   i=num;
	   i=((i-ZFX)/(YuanMa-ZFX))*80000;
	   num=i;
	}
	else if(num<(~FZX+1))
	 {
		i=~num+1;
		i=((i-FZX)/(YuanMa-FZX))*80000;  //流量计算80KP 的差压系数   3617000
		 num=i;
		num=~num+1;
	  }
   else num=0;
   
   return num;
}
//****************************************************
int32_t YS_LJ(int32_t num){
	LJI+=num;
	while(LJI>  1800000)  {LJI-=1800000; LJ++; }
	while(LJI<(-1800000)) {LJI+=1800000; LJ--; } 
    if(LJ>(999999)||LJ<(-999999))LJ=0;  else;
	
//	LJ+=num/100/5/60/60;//  小数点-2   1秒  1分 1时

	return LJ;
}
//****************************************************
void YS_YM(int32_t num){
 u32 zf;
  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
          num/=10;
	     NUM_A(num,7,0,zf,lsl);

}
//****************************************************
int32_t YS_WD(int32_t num){
u8 zf;
//	  num=num-8388607;
//	if(num>8388607){num-=8388607;num=~num;num++;}else;
	    
	num=TP1000_ohm(num);
	 num=TP1000_wd_(num);
	  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
	     NUM_A(num,7,1,zf,lwd);
	return WD;
}
/****************************************************



zf 正负号
********************************************************/
void YS_YS(int32_t num){
	int32_t cc;
	u8 zf;
#if 0
	   //                                    零点校正 负				零点校正 正
 	  if(num&0x800000){  num|=0xff000000;} else{ zf=0;} //24位负  变32位负
#else
	  num=num-8388607;
	if(num>8388607){num-=8388607;num=~num;num++;}else;
#endif	
	     BFB = (num*10) /YuanMa;     //百分比
	     if(BFB>9)BFB=9;else;
	        
		 PJ[B1]=num; if(B==1) {num=(PJ[0]+PJ[1]+PJ[2]+PJ[3]+PJ[4]+PJ[5]+PJ[6]+PJ[7]+PJ[8]+PJ[9])/10;}else;	     
 
	     cc=num;
	
//	     num+=WD;
		 num=YS_LL(num);
	  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
	     NUM_A(num,7,3,zf,lll);
	
	     num=cc;
//	     num+=WD;
	     num=YS_LL(num);    //流量
		 num=YS_LJ(num);    //累计
	  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
	     NUM_A(num,7,1,zf,ljl);
//TP1000阻值	
//		 num=cc;
//	     num=TP1000_ohm(num);
////	     num=TP1000_wd (num);
//	  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
//	     NUM_A(num,7,1,zf,lwd);
		
		 num=cc;
		 num=YS_CY(num);
	  if(num &0x80000000)	{num= ((~num)+1); zf=1;} else zf=0;//负数转换正数
	     NUM_A(num,7,3,zf,cyl);
	   
	     num=QJs;
	  if(num>18000)   {num= (36100-QJs); zf=1;} else zf=0;//负数转换正数
     	 NUM_A(num,7,2,zf,jdl); 

	    
	  
}
//******************************************
//数转ASCII
//数 ,位,小数点, 变量地址
//******************************************
void NUM_A(u32 n, u8 i, u8 d, u8 zf, u8*aa){  //数 ,位,小数点, 正负号,变量地址

	if(d==0);     		else d=i-d;	    //0不变
	if(zf==1) aa[0]=45; else aa[0]=32;  //45"-"  32" "
	
	  for(;i>0;i--)
		{
		 if(d==i&&d!=0){aa[i]=46;i--;} else; //46 ascii "."
			 aa[i]=(n%10)+48;
			 n/=10;
		 }		
}


int32_t TP1000_ohm(int32_t u)
{
  int32_t  ohm;
	double u0,i,ii, u1,u2,r2;//ii   Vs    2.498/16777125=148    1.1822  1.3158  1.249


    i=0.000000244140625;
	u0=4.096;
	r2=1000;
//	u-=(49000/2);
	
//	u2 =2.047+ii;
//	u1 =2.047-ii;
//  ohm=((u2*1004.5)/u1)*100;	
	
	
    
    u1=u*i	;
    u2=u0-u1;
    ohm=(u1*r2)/u2*100-70;	

	
return	ohm;

}	

int16_t TP1000_wd(int32_t u)
{
	u8 i=0 ,ii=0;
	u16 b=0,bb;
	u-=100000;
	
    while(u>WinDu[i])
	{
	   i++;
		if(i>51)  return 2122;
	}
   b=(WinDu[i]-WinDu[i-1])/10; 
   bb=b/2;	

   while(u>(b*ii+bb)+WinDu[i-1])ii++;// 小数
	   b=(i-1)*10+ii;
  return b;
}
int16_t TP1000_wd_(int32_t u)
{
	u8 i=0 ,ii=0;
	u16 b=0,bb;
	
	if(u>100000)
	  {
	    u-=100000;
		u*=10;
		u=u/388;
	  } 
    else
	{
	  u=100000-u;
	  u-=100000;
	  u*=10;
	  u=u/-388;
	}
 return u;
}





