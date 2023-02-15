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


/*赋值函数*/
/*入口参数：PID运算完成后的最终PWM值*/
void Load(int moto1,int moto2)
{
	//1.研究正负号，对应正反转
	if(moto1>0)	BIN1_L=1,BIN2_L=0;//正转
	else 		BIN1_L=0,BIN2_L=1;//反转
	//2.研究PWM值
	TIM_SetCompare1(TIM1,_abs(moto1));
	
	if(moto2>0)	AIN1_R=0,AIN2_R=1;//正转
	else 		AIN1_R=1,AIN2_R=0;//反转
	TIM_SetCompare4(TIM1,_abs(moto2));
}


/********************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
********************************************/
void Limit_PWM(void)
{
	 //===PWM满幅是7200 限制在7000
    if(Motor1<-7000 ) Motor1=-7000 ;
	else if(Motor1>7000 )  Motor1=7000 ;
	
	if(Motor2<-7000 ) Motor2=-7000 ;
	else if(Motor2>7000 )  Motor2=7000 ;
}

/*  绝对值函数 */
int _abs(int a)
{ 		   
	int temp;
	
	if(a<0) temp=-a;  
	else temp=a;
	
	return temp;
}

/**************************************************************************
函数功能：异常关闭电机
入口参数：倾角和电压
返回  值：无
**************************************************************************/
void Stop(float angle)
{
	if(angle<-40||angle>40)	 
	{	                                  																			 
		Motor1=0;
		Motor2=0;
	}		
}









