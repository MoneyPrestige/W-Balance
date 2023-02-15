#include "pid.h"

float Vertical_Kp=720; //1200��1500����*0.6
float Vertical_Kd=70;  //100��150����*0.6

float Velocity_Kp=0.2;
float Velocity_Ki=0.001; 

extern float Roll;

/*********************
ֱ����PD��������Kp*Ek+Kd*Ek_D
��ڣ������Ƕ�(��е��ֵ)����ʵ�Ƕȡ���ʵ���ٶ�
���ڣ�ֱ�������
*********************/
int Vertical_PID(float Med,float Angle,float gyro_Y)
{
	int PWM_out,Bias;
	
	Bias = Angle-Med;
	PWM_out=Vertical_Kp*Bias+Vertical_Kd*gyro_Y;
	
	return PWM_out;
}


/**************************************************************************
�������ܣ��ٶ�PI����
��ڲ����������������ֵ
����  ֵ���ٶȿ���PWM
**************************************************************************/
int Velocity_PID(int Left_Speed, int Right_Speed, int Target)
{
	//ע�⣡����������Ҫ��Ϊ��̬��ȫ�֣�����ÿ�ν�����Ϊδ֪�������ԣ�����
	static int PWM_out,Encoder_Err,Encoder_Integral,Encoder_Err_Lowout,Encoder_Err_Lowout_last;
		
	Encoder_Err = ((Left_Speed+Right_Speed)-Target);
	Encoder_Err_Lowout = 0.2*Encoder_Err+0.8*Encoder_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
	Encoder_Err_Lowout_last = Encoder_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
	Encoder_Integral += Encoder_Err_Lowout;
	
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
	if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===�����޷�
	
	PWM_out = Velocity_Kp*Encoder_Err_Lowout+Velocity_Ki*Encoder_Integral;
	if(Roll<-40||Roll>40) 			Encoder_Integral=0;     		//===����رպ��������
	
	return PWM_out;
}























