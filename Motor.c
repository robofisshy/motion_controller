/*
 * Motor.c
 *
 *  	@Date: 2016-4-29
 *      @Author: Yuyiqi
 *      @Brief��Timer0_interrupt,Can_interrupt
 */
//		���ٱ�	�˶���Χ���㣩
//1��	153		��70
//2��	161		��180
#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>
#include <math.h>

#define LED1 GpioDataRegs.GPADAT.bit.GPIO0
#define ENABLE_l GpioDataRegs.GPBDAT.bit.GPIO50   	//���оƬ��ʹ��
#define ENABLE_h GpioDataRegs.GPBDAT.bit.GPIO49	 	//���оƬ��ʹ��
#define Spi_STE2 GpioDataRegs.GPADAT.bit.GPIO20
#define Spi_STE1 GpioDataRegs.GPADAT.bit.GPIO21

void InitGpio();
void InitSramGpio();
void delay();
void delay_m();
void delay_1s();
void InitChipGpio();
void ECan_Init(struct ECAN_REGS ECanb_struct);
//void Motor_err();

Uint16 Axis_1;
Uint16 Axis_2;
void main()
{
	Axis_1=0;		//1�����˶�����ѡ��
	Axis_2=0;		//2�����˶�����ѡ��
	struct ECAN_REGS ECanbShadow;
	InitSysCtrl();//��ʼ������ʱ�ӣ���ֹ���Ź���·
	DINT;
	InitPieCtrl();

	IER=0x0000;
	IFR=0x0000;

	InitPieVectTable();

	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0,150,4000);		//150MHz,��ʱʱ�䣺4000us
	CpuTimer0Regs.TCR.bit.TSS=0; 				//Timer0��ʼ����

	InitChipGpio();
	InitGpio();
	LED1=1;

	InitXintf16Gpio();

	InitECan();						//CAN��ʼ��
	InitECanGpio();

	InitSpi();						//Spi��ʼ��
	InitSpiaGpio();

	InitMotor_tx();				   //�����������ʼ��

	Spi_STE2=1;
	Spi_STE1=1;

	ENABLE_l=0;						//ʹ�ܲ��оƬ
	ENABLE_h=1;
	DELAY_US(1000000);
//	Get_Motor_pos();				//�õ������ʼλ�ã�����ʼ���켣

	ECan_Init(ECanbShadow);


	IER|=0x0121;					//��CPU�ж�1,6,9
	PieCtrlRegs.PIECTRL.bit.ENPIE=1;
	//PieCtrlRegs.PIEIER1.bit.INTx7=1;//ʹ�ܶ�ʱ��0�жϣ���һ��7���ж�
	//PieCtrlRegs.PIEIER6.bit.INTx2=1;//ʹ��SPI-A�����ж�
	//PieCtrlRegs.PIEIER6.bit.INTx1=1;//ʹ��SPI-A�����ж�
	//PieCtrlRegs.PIEIER9.bit.INTx5=1;
	PieCtrlRegs.PIEIER9.bit.INTx7=1;  //ʹ��ECAN0INTB�жϣ�9.7
	EINT;							//���ж�INTMʹ��
	ERTM;							//ʹ����ʵʱ�ж� DBGM


	while(1)
		{
			//�ȴ�����CAN���ߴ���������
		}
}
void InitGpio()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0=0;
	GpioCtrlRegs.GPADIR.bit.GPIO0=1;
	EDIS;
}
void InitChipGpio()
{
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO49=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO49=1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO50=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO50=1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=0;
	GpioCtrlRegs.GPAPUD.bit.GPIO20=0;
	GpioCtrlRegs.GPADIR.bit.GPIO20=1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO21=0;
	GpioCtrlRegs.GPAPUD.bit.GPIO21=0;
	GpioCtrlRegs.GPADIR.bit.GPIO21=1;
	EDIS;
}
void Motor1_T()
{
	Uint16 i;
	Spi_STE1=0;
	DELAY_US(2);
	for(i=0;i<16;i++)
	{
		SpiaRegs.SPITXBUF=Master_tx[i];
		delay();
	}
	Spi_STE1=1;
}
void Motor2_T()
{
	Uint16 i;
	//Master_tx[15]=CRC_table(Master_tx,15);	//add CRC code
	Spi_STE2=0;
	for(i=0;i<16;i++)
	{
		SpiaRegs.SPITXBUF=Master_tx[i];
		delay();
	}
	Spi_STE2=1;
}
void Motor_R()
{
	register Uint16 i;
	for(i=0;i<16;i++)
	{
		Master_rx[i]=SpiaRegs.SPIRXBUF;
		delay();
	}
}
void Get_Motor_pos()
{
	if(Axis_1==1)
	{
		Motor1_T();
		Motor_R();
		while(Master_rx[0]!=0x0708||Master_rx[15]!=0x0405)
		{
			DELAY_US(500000);
			Motor1_T();
			Motor_R();
		}
		Init_Traj(Master_rx[8],Master_rx[7]);
	}
	if(Axis_2==1)
	{
		Motor2_T();
		Motor_R();
		while(Master_rx[0]!=0x0708||Master_rx[15]!=0x0405)
		{
			DELAY_US(500000);
			Motor2_T();
			Motor_R();
		}
		//Init_Traj(Master_rx[9],Master_rx[8]);
		Init_Traj(Master_rx[8],Master_rx[7]);
	}
}
void ECan_Init(struct ECAN_REGS ECanb_struct)
{
	ECanbMboxes.MBOX25.MSGID.all=0x95555555;			//MBOX25 ID


	// Configure Mailbox under test as a Transmit mailbox

	ECanb_struct.CANMD.all = ECanbRegs.CANMD.all;
	ECanb_struct.CANMD.bit.MD25 = 1;
	ECanbRegs.CANMD.all = ECanb_struct.CANMD.all;
	//	 Enable Mailbox under test

	ECanb_struct.CANME.all = ECanbRegs.CANME.all;
	ECanb_struct.CANME.bit.ME25 = 1;
	ECanbRegs.CANME.all = ECanb_struct.CANME.all;

	//	 Write to DLC field in Master Control reg

	ECanbMboxes.MBOX25.MSGCTRL.bit.DLC = 8;
}
void delay()
{
	int i;
	for(i=0;i<1000;i++);
}
void delay_m()
{
	int i;
	for(i=0;i<3000;i++);
}
void error()
{
	asm("ESTOP0");
	for(;;);
}


