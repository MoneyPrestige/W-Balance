#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"


void ENCODER_TIM4_Init(void);
void ENCODER_TIM3_Init(void);
int Read_Encoder(u8 TIMx);


#endif /* _ENCODER_H */


