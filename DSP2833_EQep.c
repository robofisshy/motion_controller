/*
 * DSP2833_EQep.c
 *
 *  Created on: 2016-1-3
 *      Author: Yuyiqi
 */
#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>

void InitEQep()
{
	EQep1Regs.QDECCTL.bit.QSRC=0;		//正交计数模式
	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;	//仿真器断点时计数器不受影响
	EQep1Regs.QEPCTL.bit.PCRM=0;		//索引事件时位置计数器复位
	EQep1Regs.QPOSINIT=0;
	EQep1Regs.QPOSMAX=0x1;
	EQep1Regs.QEPCTL.bit.QPEN=1;		//正交位置计数器使能
}
void InitEQepGpio()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=0;
	EDIS;
}




