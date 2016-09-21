/*
 * InitMotor.c
 *
 *  	@Date: 2016-4-29
 *      @Author: Yuyiqi
 *      @brief:  Initialize the Motor
 */
#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>

int32 Master_tx[16];
//int16 Master_tx[16];
Uint16 Master_rx[16];
//float32 Master_rx[16];
Uint16 Motor_err[16]=0;

/*********************CSV模式主机发送数据********************/
//通灵协议 第1个字0x0F,第二个字固定值 0x2，第3个字速度 其他不用管

void InitMotor_tx()		//无CRC位的初始化
{
	Master_tx[0]=0x7e81;		//主机发送起始位
	Master_tx[1]=0x000F;		//初始化控制字
	Master_tx[2]=0x2;			//固定值 0x2
	Master_tx[3]=0;				//初始化速度
	Master_tx[4]=0x0;
	Master_tx[5]=0x0;
	Master_tx[6]=0x0;
	Master_tx[7]=0x0;
	Master_tx[8]=0x0;
	Master_tx[9]=0x0;
	Master_tx[10]=0x0;
	Master_tx[11]=0x0;
	Master_tx[12]=0x0;
	Master_tx[13]=0x0;
	Master_tx[14]=0x0;
	Master_tx[15]=0x55aa;		//主机发送结束位
}
/*void InitMotor_tx()		//含CRC位的初始化
{
	Master_tx[0]=0x7e81;		//主机发送起始位
	Master_tx[1]=0x000F;		//初始化控制字
	Master_tx[2]=0x2;			//固定值 0x2
	Master_tx[3]=0;			//初始化速度
	Master_tx[4]=0x0;
	Master_tx[5]=0x0;
	Master_tx[6]=0x0;
	Master_tx[7]=0x0;
	Master_tx[8]=0x0;
	Master_tx[9]=0x0;
	Master_tx[10]=0x0;
	Master_tx[11]=0x0;
	Master_tx[12]=0x0;
	Master_tx[13]=0x0;
	Master_tx[14]=0x55aa;
	Master_tx[15]=0x0;		//主机发送结束位
}*/
