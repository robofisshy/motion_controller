/*
 * InitTrajectory.c
 *
 *  	@Date: 2016-4-29
 *      @Author: Yuyiqi
 *      @Brief: Calculate the trajectory.
 */
#include <DSP2833x_Device.h>
#include <DSP2833x_Examples.h>
#include <math.h>

#define pi 3.141592653
float64 Target1[1001];			//1号轴轨迹点
float64 Target2[1001];			//2号轴轨迹点
float64 Actual0[1001];			//实际位置点
float64 act_v[1001];			//实际速度值


void Init_Traj(float64 Init_circle,float64 Init_num)
{
	Uint16 Sample=0;
	float64 angle=0;
	//float64 i=0;
	act_v[0]=0;
	Actual0[0]=Init_circle*65536+Init_num;
	if(Axis_1)
	{
		for(Sample=0;Sample<=1000;Sample++)
		{
			angle=2*Sample*pi/1000;
			Target1[Sample]=Init_circle*65536+Init_num+65536*Init_pos*(1-cos(angle));
			/*if(Sample<=100)
				Target[Sample]=floor(Init_circle*65536+Init_num+65536*3*(i/100));
			else
				Target[Sample]=floor(Init_circle*65536+Init_num+65536*3+65536*50*((i-100)/900));
			i++;*/
			//Target[Sample]=floor(Init_circle*65536+Init_num+65536*50*(Sample/1000));
			//Target[Sample]=floor(Init_circle*65536+Init_num+65536*50*(i/1000));
			//i++;
		}
	}
	if(Axis_2)
		{
			for(Sample=0;Sample<=1000;Sample++)
			{
				angle=2*Sample*pi/1000;
				Target2[Sample]=Init_circle*65536+Init_num+65536*Init_pos*(1-cos(angle));
				/*if(Sample<=100)
					Target[Sample]=floor(Init_circle*65536+Init_num+65536*3*(i/100));
				else
					Target[Sample]=floor(Init_circle*65536+Init_num+65536*3+65536*50*((i-100)/900));
				i++;*/
				//Target[Sample]=floor(Init_circle*65536+Init_num+65536*50*(Sample/1000));
				//Target[Sample]=floor(Init_circle*65536+Init_num+65536*50*(i/1000));
				//i++;
			}
		}
}


