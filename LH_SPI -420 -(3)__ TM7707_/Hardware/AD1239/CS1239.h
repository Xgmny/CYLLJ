#ifndef __CS1239_H
#define __CS1239_H


#include "stm32f10x.h"

#define ADC_AD() 		 { CS1239_io_write(0x01, 0x00);    CS1239_io_write(0x02, 0x5d);	}//5:40HZ    7:80HZ  64±∂ 
#define ADC_WD()		 { CS1239_io_write(0x01, 0x22);    CS1239_io_write(0x02, 0x50);	}//71:80Hz


#define CS_H()   GPIO_SetBits(GPIOB, GPIO_Pin_12);
#define CS_L()   GPIO_ResetBits(GPIOB, GPIO_Pin_12);

#define SCK_H()  {GPIO_SetBits(GPIOB, GPIO_Pin_13);ndelay(1);}
#define SCK_L()  {GPIO_ResetBits(GPIOB, GPIO_Pin_13);ndelay(1);}

#define SDA_H()  {GPIO_SetBits(GPIOB, GPIO_Pin_15);ndelay(1);}
#define SDA_L()  {GPIO_ResetBits(GPIOB, GPIO_Pin_15);ndelay(1);}

#define ENREF 3
#define ENADC 2
#define ENLDO 1
#define IMOD 7
#define FS_SEL 6
#define INNS 3
#define INPS 0
#define DR 5    
#define BUFBP 4
#define PGA 2
#define ADGN 0
#define ADREFS 2
#define LDOS 0
#define READ 0X09

#define AD123 1 //1 «1239   0 «¿œ∞Â

void Delay1us(void);
void Delay1ms(void);
void delay_ms_cs(__IO uint16_t ms);
void CS1239_Init(void);
unsigned char Read_Config(void);
int32_t Read_CS1239(void);

void CS1239_init(u8);
int32_t CS1239_io_read(uint8_t addr, uint8_t* buf);
static void send(uint8_t data);
static void ndelay(uint32_t time);
static uint8_t read(void);
int32_t CS1239_io_write(uint8_t addr, uint8_t value);
int32_t CS1239_read(uint8_t addr);

void OUT_IN(void);
void OUT_OUT(void);
void AD_AD(uint8_t* buf);
void AD_WD(uint8_t*_buf);
void ADC_EN(void);
void ADC_DIS(void);


//*******************************


#endif


