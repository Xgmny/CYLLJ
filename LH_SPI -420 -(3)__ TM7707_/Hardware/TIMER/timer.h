#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "gui.h"

#define EA_1   __set_PRIMASK(1);//__set_FAULTMASK(1)    ¿ª
#define EA_0   __set_PRIMASK(0);//__set_FAULTMASK(0)   ¹Ø

extern u8 sec; 
extern u8 ms200;

void WBZD_Init(void);
void TIM3_init(u16 arr,u16 psc);
void TIM4_init(u16 arr,u16 psc);
void PVD_init(void);
void Made_Data(void);
void LJLL_Data(void);
void N_A(u32 n,u8 *a,u8 w);
 
#endif
