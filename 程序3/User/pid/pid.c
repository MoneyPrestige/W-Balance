#include "pid.h"

float Vertical_Kp=720; //1200（1500，）*0.6
float Vertical_Kd=70;  //100（150，）*0.6

float Velocity_Kp=0.2;
float Velocity_Ki=0.001; 

extern float Roll;

/*********************
直立环PD控制器：Kp*Ek+Kd*Ek_D
入口：期望角度(机械中值)、真实角度、真实角速度
出口：直立环输出
*********************/
int Vertical_PID(float Med,float Angle,float gyro_Y)
{
	int PWM_out,Bias;
	
	Bias = Angle-Med;
	PWM_out=Vertical_Kp*Bias+Vertical_Kd*gyro_Y;
	
	return PWM_out;
}


/**************************************************************************
函数功能：速度PI控制
入口参数：电机编码器的值
返回  值：速度控制PWM
**************************************************************************/
int Velocity_PID(int Left_Speed, int Right_Speed, int Target)
{
	//注意！！！误差变量要设为静态或全局，否则每次进来都为未知，数不对！！！
	static int PWM_out,Encoder_Err,Encoder_Integral,Encoder_Err_Lowout,Encoder_Err_Lowout_last;
		
	Encoder_Err = ((Left_Speed+Right_Speed)-Target);
	Encoder_Err_Lowout = 0.2*Encoder_Err+0.8*Encoder_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
	Encoder_Err_Lowout_last = Encoder_Err_Lowout;//防止速度过大的影响直立环的正常工作。
	Encoder_Integral += Encoder_Err_Lowout;
	
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
	if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===积分限幅
	
	PWM_out = Velocity_Kp*Encoder_Err_Lowout+Velocity_Ki*Encoder_Integral;
	if(Roll<-40||Roll>40) 			Encoder_Integral=0;     		//===电机关闭后清除积分
	
	return PWM_out;
}























