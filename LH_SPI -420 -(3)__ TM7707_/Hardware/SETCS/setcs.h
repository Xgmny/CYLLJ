#ifndef __SETCS_H
#define __SETCS_H	 
#include "sys.h"
#include "pic.h"

static int col;
static int row;
static u8 page;
static u8 smode;
static u8 wz;

void SET_IN(void);
void SET_COME(void);
void CAN_Answer(void);
void CAN_SAVE(void);


#endif
