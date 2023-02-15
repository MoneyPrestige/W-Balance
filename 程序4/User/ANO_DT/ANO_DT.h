#ifndef _ANO_DT_H
#define _ANO_DT_H

#include "stm32f10x.h"


/* 将多字节数据拆分成单字节数据  */ 
#define BYTE0(dwTemp)		(*(char *)(&dwTemp))
#define BYTE1(dwTemp)		(*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)		(*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)		(*((char *)(&dwTemp) + 3))




void ANODT_SendF1(s16 _a, s16 _b, s32 _c);
void ANODT_Send03(s16 _a, s16 _b, s16 _c, u8 _fu);
void ANODT_Send01(s16 _ax, s16 _ay, s16 _az, s16 _gx, s16 _gy, s16 gz, u8 _shock);

#endif /* _ANO_DT_H */

