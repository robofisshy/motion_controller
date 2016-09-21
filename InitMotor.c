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

/*********************CSVģʽ������������********************/
//ͨ��Э�� ��1����0x0F,�ڶ����̶ֹ�ֵ 0x2����3�����ٶ� �������ù�

void InitMotor_tx()		//��CRCλ�ĳ�ʼ��
{
	Master_tx[0]=0x7e81;		//����������ʼλ
	Master_tx[1]=0x000F;		//��ʼ��������
	Master_tx[2]=0x2;			//�̶�ֵ 0x2
	Master_tx[3]=0;				//��ʼ���ٶ�
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
	Master_tx[15]=0x55aa;		//�������ͽ���λ
}
/*void InitMotor_tx()		//��CRCλ�ĳ�ʼ��
{
	Master_tx[0]=0x7e81;		//����������ʼλ
	Master_tx[1]=0x000F;		//��ʼ��������
	Master_tx[2]=0x2;			//�̶�ֵ 0x2
	Master_tx[3]=0;			//��ʼ���ٶ�
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
	Master_tx[15]=0x0;		//�������ͽ���λ
}*/
