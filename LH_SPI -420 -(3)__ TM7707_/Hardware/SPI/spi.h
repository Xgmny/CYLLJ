/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/
#ifndef _SPI_H_
#define _SPI_H_
#include "sys.h"

//本测试程序使用的是硬件SPI接口驱动
//SPI时钟信号以及SPI读、写信号引脚不可更改
//SPI的时钟引脚定义固定为PB13
//SPI的读数据引脚定义固定为PB14
//SPI的写数据引脚定义固定为PB15
 
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
void SPI1_Init(void);
void SPI2_Init(void);
void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet);

#endif
