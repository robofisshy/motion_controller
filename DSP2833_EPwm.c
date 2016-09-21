/*
 * DSP2833_EV.c
 *
 *  Created on: 2015-12-30
 *      Author: Yuyiqi
 */
#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>

#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif
#define PWM_CLK   10e3
#define SP        CPU_CLK/(2*PWM_CLK)

void InitEPwm()
{
	InitEPwmGpio();
	//时间基准子模块初始化
	EPwm1Regs.TBCTR=0x0000;				//基准计数器置零
	EPwm1Regs.TBPRD=SP;					//SP=150e6/(2*10e3)
	EPwm1Regs.TBCTL.bit.CTRMODE=0x2;	//计数器模式为递增递减计数
	EPwm1Regs.TBCTL.bit.PHSEN=0x1;		//允许相位控制
	EPwm1Regs.TBCTL.bit.PRDLD=0x0;		//当CTR=0时 将映射寄存器加载到当前
	EPwm1Regs.TBCTL.bit.SYNCOSEL=0x0;	//同步输出信号源为EPWMxSYNC
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=0x0;	//预分频系数:HSPCLKDIV*CLKDIV=1
	EPwm1Regs.TBCTL.bit.CLKDIV=0x0;
	//比较功能子模块初始化
	EPwm1Regs.CMPCTL.bit.SHDWAMODE=0x1;	//寄存器为立即装载模式
	EPwm1Regs.CMPCTL.bit.SHDWBMODE=0x1;
	EPwm1Regs.CMPA.half.CMPA=SP/4;		//计数比较A寄存器=SP/2
	EPwm1Regs.CMPB=SP/4;				//计数比较B寄存器=SP/2
	//动作限定子模块初始化
	EPwm1Regs.AQCTLA.bit.CAU=AQ_SET;	//当计数器=CMPA寄存器且计数器递增时，EPWMxA输出高
	EPwm1Regs.AQCTLA.bit.CAD=AQ_CLEAR;	//当计数器=CMPA寄存器且计数器递减时，EPWMxA输出低
}
void InitEPwmGpio()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0=1;
	GpioCtrlRegs.GPADIR.bit.GPIO0=1;
	EDIS;
}




