#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ANO_DT.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpuiic.h"
#include "mpu6050.h"
#include "exti.h"
#include "encoder.h"
#include "pwm.h"
#include "motor.h"
#include "oled.h"


int main(void)
{	
	delay_init();
	uart2_init(500000);
	MPU_Init();
	while( mpu_dmp_init() )
	{
		printf("MPU6050 Error");
		delay_ms(200);
	}
	EXTI_Config();
	ENCODER_TIM4_Init();
	ENCODER_TIM3_Init();
	PWM_TIM1_Init(7199, 0);
	MOTOR_GPIOB_Init();
	OLED_Init();                  
	OLED_Clear();					
	oled_first_show();
	
	
	while(1)
	{
		oled_show();
		delay_ms(50); 
	}		
	
}

