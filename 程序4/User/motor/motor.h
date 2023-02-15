#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"
#include "sys.h"

#define BIN1_L		PBout(14)
#define BIN2_L		PBout(15)
#define AIN1_R		PBout(12)
#define AIN2_R		PBout(13)


void MOTOR_GPIOB_Init(void);
void Limit_PWM(void);
void Load(int moto1,int moto2);
int _abs(int a);
void Stop(float angle);


#endif /* _MOTOR_H */


