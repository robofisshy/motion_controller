/*

 * PID_calculate.c
 *
 *  Created on: 2016-5-10
 *      Author: Administrator
*/

#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>

//float m_kp = 0.002;//0.0015;//1/0.5;//1/8.0;         //PID增益
//float m_ki= 0;//0.0005;//1/0.04;
float m_kd= 0.01;//0.02;
float e,ec,last_e=0,e_sum=0;
float ie,de;						//PID积分系数，微分系数
float Ts=4e-4;              //采样周期400us;
float64 Error[201];
Uint16 err_count=0;
int16 vel=0;
int16 PID_control(float64 Target_position,float64 Actual_position)
{
	//e=Target_position-Circle_num*65536-Actual_position;
	e=Target_position-Actual_position;

	if(e>=10000)
		e=10000;
	else if(e<=-10000)
		e=-10000;
	Error[err_count]=e;
	e_sum+=e;
	ec=e-last_e;
	ie=Ts*ec;
    de=ec/Ts;
    //velocity=m_kp*e+m_ki*ie+m_kd*de;
    //velocity=m_kp*ec+m_ki*e;		//增量式
    vel=m_kp*e+m_ki*e_sum;		//位置式
    last_e=e;
    err_count++;
   	return vel;
}







