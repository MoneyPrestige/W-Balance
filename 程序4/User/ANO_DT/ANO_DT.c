#include "ANO_DT.h"
#include "usart.h"

u8 DataToSend[100];

void ANODT_SendF1(s16 _a, s16 _b, s32 _c)
{
	u8 _cnt = 0;
	u8 sc = 0;
	u8 ac = 0;
	u8 i = 0;
	
	DataToSend[_cnt++] = 0xAA;
	DataToSend[_cnt++] = 0xFF;
	DataToSend[_cnt++] = 0xF1;
	DataToSend[_cnt++] = 8;
	
	DataToSend[_cnt++] = BYTE0(_a); 	// 小端模式：低字节在前 	
	DataToSend[_cnt++] = BYTE1(_a);
	
	DataToSend[_cnt++] = BYTE0(_b);
	DataToSend[_cnt++] = BYTE1(_b);
	
	DataToSend[_cnt++] = BYTE0(_c);
	DataToSend[_cnt++] = BYTE1(_c);
	DataToSend[_cnt++] = BYTE2(_c);
	DataToSend[_cnt++] = BYTE3(_c);
	
	for(i=0; i<DataToSend[3]+4; i++) 	// DataToSend[3]为数据长度 
	{
		sc += DataToSend[i];
		ac += sc;
	}
	
	DataToSend[_cnt++] = sc;
	DataToSend[_cnt++] = ac;
	
	for(i=0;i<_cnt;i++)
	{
		usart2_send_char(DataToSend[i]);	//发送数据到串口2
	}
	
}


void ANODT_Send03(s16 _a, s16 _b, s16 _c, u8 _fu)
{
	u8 _cnt = 0;
	u8 sc = 0;
	u8 ac = 0;
	u8 i = 0;
	
	DataToSend[_cnt++] = 0xAA;
	DataToSend[_cnt++] = 0xFF;
	DataToSend[_cnt++] = 0x03;
	DataToSend[_cnt++] = 7;
	
	DataToSend[_cnt++] = BYTE0(_a); 	// 小端模式：低字节在前 	
	DataToSend[_cnt++] = BYTE1(_a);
	
	DataToSend[_cnt++] = BYTE0(_b);
	DataToSend[_cnt++] = BYTE1(_b);
	
	DataToSend[_cnt++] = BYTE0(_c);
	DataToSend[_cnt++] = BYTE1(_c);
	
	DataToSend[_cnt++] = BYTE0(_fu);
	
	for(i=0; i<DataToSend[3]+4; i++) 	// DataToSend[3]为数据长度 
	{
		sc += DataToSend[i];
		ac += sc;
	}
	
	DataToSend[_cnt++] = sc;
	DataToSend[_cnt++] = ac;
	
	for(i=0;i<_cnt;i++)
	{
		usart2_send_char(DataToSend[i]);	//发送数据到串口2
	}
	
}

void ANODT_Send01(s16 _ax, s16 _ay, s16 _az, s16 _gx, s16 _gy, s16 _gz, u8 _shock)
{
	u8 _cnt = 0;
	u8 sc = 0;
	u8 ac = 0;
	u8 i = 0;
	
	DataToSend[_cnt++] = 0xAA;
	DataToSend[_cnt++] = 0xFF;
	DataToSend[_cnt++] = 0x01;
	DataToSend[_cnt++] = 13;
	
	DataToSend[_cnt++] = BYTE0(_ax); 	// 小端模式：低字节在前 	
	DataToSend[_cnt++] = BYTE1(_ax);
	DataToSend[_cnt++] = BYTE0(_ay);
	DataToSend[_cnt++] = BYTE1(_ay);
	DataToSend[_cnt++] = BYTE0(_az);
	DataToSend[_cnt++] = BYTE1(_az);
	
	DataToSend[_cnt++] = BYTE0(_gx);
	DataToSend[_cnt++] = BYTE1(_gx);
	DataToSend[_cnt++] = BYTE0(_gy);
	DataToSend[_cnt++] = BYTE1(_gy);
	DataToSend[_cnt++] = BYTE0(_gz);
	DataToSend[_cnt++] = BYTE1(_gz);
	
	DataToSend[_cnt++] = BYTE0(_shock);
	
	for(i=0; i<DataToSend[3]+4; i++) 	// DataToSend[3]为数据长度 
	{
		sc += DataToSend[i];
		ac += sc;
	}
	
	DataToSend[_cnt++] = sc;
	DataToSend[_cnt++] = ac;
	
	for(i=0;i<_cnt;i++)
	{
		usart2_send_char(DataToSend[i]);	//发送数据到串口2
	}
	
}











