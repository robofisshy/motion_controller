/********************************
  Motor.h
 
   Created on 2016-3-28
       Author Administrator
 *******************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>
#include <math.h>
/*******电机变量设置***********/

extern int32 Master_tx[16];
//extern int16 Master_tx[16];
extern Uint16 Master_rx[16];
//extern float32 Master_rx[16];
//extern Uint16 Motor_err[16];

#pragma DATA_SECTION (Target1,"ZONE6DATA");
#pragma DATA_SECTION (Target2,"ZONE6DATA");
#pragma DATA_SECTION (act_v,"ZONE6DATA");
#pragma DATA_SECTION (Actual0,"ZONE6DATA");

extern float64 Target1[1001];
extern float64 Target2[1001];
extern float64 Actual0[1001];

extern float64 act_v[1001];

extern float m_kp;          //PID增益
extern float m_ki;			//1/0.04;
extern float m_kd;			//0.02;
extern float e,ec,last_e,e_sum;
extern float ie,de;						//PID积分系数，微分系数
extern float Ts;              //采样周期400us;
extern int16 vel;
extern Uint16 err_count;
extern Uint16 Axis_1;
extern Uint16 Axis_2;
extern Uint16 Init_pos;

int16 PID_control(float64 Target_position,float64 Actual_position);
extern void Init_Traj(float64 Init_circle,float64 Init_num);
extern void InitECan();
extern void InitECanGpio();
extern void Get_Motor_pos();
extern void Motor_R();
extern void Motor1_T();
extern void Motor2_T();
extern void InitMotor_tx();
extern int32 CRC_cal(int32 *arr_buff,Uint16 len);
extern Uint16 CRC_Table(int32 *arr_buff,Uint16 len);

#endif MOTOR_H_

