#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "ANO_DT.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpuiic.h"
#include "mpu6050.h"
#include "pid.h"
#include "motor.h"
#include "encoder.h"

float Med_Angle = 0;	//机械中值
int Target_Speed = 0; //目标速度
float Pitch,Roll,Yaw;	//俯仰角,翻滚角,偏航角
s16 gyrox,gyroy,gyroz;	//角速度
s16 aacx,aacy,aacz;		//加速度		
int Motor1=0,Motor2=0;	
int Vertical_out,Velocity_out;
int Left_Speed,Right_Speed;

static void EXTI_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
}

void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//配置中断优先级
	EXTI_NVIC_Config();
	
	//初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//初始化EXTI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);   // 最后配置的端口使用中断，不能同时使用中断线
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line5;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		while(mpu_dmp_get_data(&Pitch, &Roll, &Yaw) != 0);
		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);	//陀螺仪 
		Left_Speed = Read_Encoder(4);
		Right_Speed = -Read_Encoder(3);
		//MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//加速度 
		//temp = MPU_Get_Temperature();
		//printf("temp=%d\n",temp/100);
		//ANODT_Send03(Roll*100, Pitch*100, Yaw*100, 0);
		//ANODT_Send01(aacx, aacy, aacz, gyrox, gyroy, gyroz, 1);
		//printf("Pitch=%f, Roll=%f, Yaw=%f\n\n\n\n", Pitch, Roll, Yaw);
		//printf("gyrox=%d, gyroy=%d, gyroz=%d\n\n\n\n", gyrox, gyroy, gyroz);
		//printf("aacx=%d, aacy=%d, aacz=%d\n\n\n\n", aacx, aacy, aacz);
		//delay_ms(5);
		
		Velocity_out = Velocity_PID(Left_Speed, Right_Speed, Target_Speed);
		Vertical_out = Vertical_PID(Velocity_out+Med_Angle, Roll, gyroy);
		
		Motor1 = Vertical_out;                 
		Motor2 = Vertical_out;        
		
	    Limit_PWM();
		Stop(Roll);					//注意停止和装载顺序
		Load(Motor1, Motor2);
		
	}
	EXTI_ClearITPendingBit(EXTI_Line5);
}



