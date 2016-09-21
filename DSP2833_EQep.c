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
	EQep1Regs.QDECCTL.bit.QSRC=0;		//��������ģʽ
	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;	//�������ϵ�ʱ����������Ӱ��
	EQep1Regs.QEPCTL.bit.PCRM=0;		//�����¼�ʱλ�ü�������λ
	EQep1Regs.QPOSINIT=0;
	EQep1Regs.QPOSMAX=0x1;
	EQep1Regs.QEPCTL.bit.QPEN=1;		//����λ�ü�����ʹ��
}
void InitEQepGpio()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=0;
	EDIS;
}




