#ifndef __TM7707_H
#define __TM7707_H
#include "sys.h"
#include "delay.h"

//#define SCLK   PBout(13)
//#define DOUT   PBout(14)
//#define DIO    PBout(15)
//#define DII    PBin(15)
//#define DRDY_1   PBin(8)
//#define DRDY_2   PBin(9)
//#define RESET  PBout(12)
//#define CS_1   PBout(10)
//#define CS_2   PBout(11)

#define __CH1_GAIN_BIPOLAR_BUF	(GAIN_64 | BIPOLAR | BUF_EN)
#define __CH2_GAIN_BIPOLAR_BUF	(GAIN_2 | BIPOLAR | BUF_EN)
	#define RESET_0()	(GPIO_ResetBits(GPIOB,GPIO_Pin_12))
	#define RESET_1()	(GPIO_SetBits(GPIOB,GPIO_Pin_12))
	#define CS1_0()		GPIO_ResetBits(GPIOB,GPIO_Pin_10)
	#define CS1_1()		GPIO_SetBits(GPIOB,GPIO_Pin_10)
	#define CS2_0()		GPIO_ResetBits(GPIOB,GPIO_Pin_11)
	#define CS2_1()		GPIO_SetBits(GPIOB,GPIO_Pin_11)
	#define SCK_0()		GPIO_ResetBits(GPIOB,GPIO_Pin_13)
	#define SCK_1()		GPIO_SetBits(GPIOB,GPIO_Pin_13)
	#define DI_0()		GPIO_ResetBits(GPIOB,GPIO_Pin_15)
	#define DI_1()		GPIO_SetBits(GPIOB,GPIO_Pin_15)

	#define DO_IS_HIGH()	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == Bit_SET)

	#define DRDY1_IS_LOW()	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == Bit_RESET)
	#define DRDY2_IS_LOW()	(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == Bit_RESET)



void TM7707_init(void); //≥ı ºªØ
void save_data(void);
u8 read_byte1 ();

static void TM7705_SyncSPI(void);
static void TM7705_Send8Bit(uint8_t _data);
static uint8_t TM7705_Recive8Bit(void);
 void TM7705_WriteByte(uint8_t _data);
static void TM7705_Write3Byte(uint32_t _data);
static uint8_t TM7705_ReadByte(void);
static uint16_t TM7705_Read2Byte(void);
 uint32_t TM7705_Read3Byte(void);
void TM7705_WaitDRDY(void);
static void TM7705_ResetHard(void);
static void TM7705_Delay(void);
void TM7705_CalibSelf(uint8_t _ch);
uint32_t TM7705_ReadAdc(uint8_t _ch);
void TM7705_WriteReg(uint8_t _RegID, uint32_t _RegValue);


void DIO_IN( );
void DIO_OUT( );

#endif

