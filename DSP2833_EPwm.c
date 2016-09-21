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
	//ʱ���׼��ģ���ʼ��
	EPwm1Regs.TBCTR=0x0000;				//��׼����������
	EPwm1Regs.TBPRD=SP;					//SP=150e6/(2*10e3)
	EPwm1Regs.TBCTL.bit.CTRMODE=0x2;	//������ģʽΪ�����ݼ�����
	EPwm1Regs.TBCTL.bit.PHSEN=0x1;		//������λ����
	EPwm1Regs.TBCTL.bit.PRDLD=0x0;		//��CTR=0ʱ ��ӳ��Ĵ������ص���ǰ
	EPwm1Regs.TBCTL.bit.SYNCOSEL=0x0;	//ͬ������ź�ԴΪEPWMxSYNC
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=0x0;	//Ԥ��Ƶϵ��:HSPCLKDIV*CLKDIV=1
	EPwm1Regs.TBCTL.bit.CLKDIV=0x0;
	//�ȽϹ�����ģ���ʼ��
	EPwm1Regs.CMPCTL.bit.SHDWAMODE=0x1;	//�Ĵ���Ϊ����װ��ģʽ
	EPwm1Regs.CMPCTL.bit.SHDWBMODE=0x1;
	EPwm1Regs.CMPA.half.CMPA=SP/4;		//�����Ƚ�A�Ĵ���=SP/2
	EPwm1Regs.CMPB=SP/4;				//�����Ƚ�B�Ĵ���=SP/2
	//�����޶���ģ���ʼ��
	EPwm1Regs.AQCTLA.bit.CAU=AQ_SET;	//��������=CMPA�Ĵ����Ҽ���������ʱ��EPWMxA�����
	EPwm1Regs.AQCTLA.bit.CAD=AQ_CLEAR;	//��������=CMPA�Ĵ����Ҽ������ݼ�ʱ��EPWMxA�����
}
void InitEPwmGpio()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0=1;
	GpioCtrlRegs.GPADIR.bit.GPIO0=1;
	EDIS;
}




