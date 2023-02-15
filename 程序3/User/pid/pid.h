#ifndef _PID_H
#define _PID_H

#include "stm32f10x.h"


int Vertical_PID(float Med,float Angle,float gyro_Y);
int Velocity_PID(int Left_Speed, int Right_Speed, int Target);

#endif /* _PID_H */


