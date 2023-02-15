#include "motor.h"

extern int Motor1,Motor2;

void MOTOR_GPIOB_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
	
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}


/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
void Load(int moto1,int moto2)
{
	//1.�о������ţ���Ӧ����ת
	if(moto1>0)	BIN1_L=1,BIN2_L=0;//��ת
	else 		BIN1_L=0,BIN2_L=1;//��ת
	//2.�о�PWMֵ
	TIM_SetCompare1(TIM1,_abs(moto1));
	
	if(moto2>0)	AIN1_R=0,AIN2_R=1;//��ת
	else 		AIN1_R=1,AIN2_R=0;//��ת
	TIM_SetCompare4(TIM1,_abs(moto2));
}


/********************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
********************************************/
void Limit_PWM(void)
{
	 //===PWM������7200 ������7000
    if(Motor1<-7000 ) Motor1=-7000 ;
	else if(Motor1>7000 )  Motor1=7000 ;
	
	if(Motor2<-7000 ) Motor2=-7000 ;
	else if(Motor2>7000 )  Motor2=7000 ;
}

/*  ����ֵ���� */
int _abs(int a)
{ 		   
	int temp;
	
	if(a<0) temp=-a;  
	else temp=a;
	
	return temp;
}

/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ����
**************************************************************************/
void Stop(float angle)
{
	if(angle<-40||angle>40)	 
	{	                                  																			 
		Motor1=0;
		Motor2=0;
	}		
}









