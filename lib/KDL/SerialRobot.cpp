/*
 * robot.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: root
 */

#include "SerialRobot.h"

robot::robot() {

}

robot::~robot() {
}

///////////////////////////////////////
// RIGHT
///////////////////////////////////////


void robot::robot_update_R(void)
{
	Eigen::Vector3f CoM_URDF[6];
    pKin = new HYUMotionKinematics::PoEKinematics();
    pCoM = new HYUMotionKinematics::PoEKinematics();
    pDyn = new HYUMotionDynamics::Liedynamics(*pKin, *pCoM);

	w[0] << 0, 0, 1; //(6.874 deg)Tilted axis due to socket //0, -1, 0;
	w[1] << 0, 1, 0;
	w[2] << 0, 0, 1;
	w[3] << -1, 0, 0;
	w[4] << 0, 0, 1;
	w[5] << 0, 1, 0;
	/*
	p[0] << 0, 0, 0;
	p[1] << 0, - LINK_12, 0;
	p[2] << 0, 0, 0;
	p[3] << 0, - LINK_23 - LINK_34, 0;
	p[4] << 0, 0, 0;
	p[5] << 0, - LINK_23 - LINK_45 - LINK_34 - LINK_56, 0;

	L[0] << 0, -LINK_12, 0;
	L[1] << 0, -LINK_23, 0;
	L[2] << 0, -LINK_34, 0;
	L[3] << 0, -LINK_45, 0;
	L[4] << 0, -LINK_56, 0;
	L[5] << 0, -LINK_6e, 0;
	*/
	w[0] << 0,0,1;
	w[1] << 0,1,0;
	w[2] << 0,0,1;
	w[3] << -1,0,0;
	w[4] << 0,0,1;
	w[5] << 0,1,0;

	p[0]<<BASE_X,BASE_Y,BASE_Z+LINK_01;
	p[1]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12;
	p[2]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23;
	p[3]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34;
	p[4]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45;
	p[5]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45+LINK_56;

	L[0]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12;
	L[1]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23;
	L[2]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34;
	L[3]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45;
	L[4]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45+LINK_56;
	L[5]<<BASE_X,BASE_Y,BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45+LINK_56+LINK_6E;

	CoM_URDF[0]<< 0.0 ,0 ,0.049473;
	CoM_URDF[1]<< 0.001501, 0, 0.042572;
	CoM_URDF[2]<< 0.000454 ,0.002601 ,0.084558;
	CoM_URDF[3]<< -0.002133 ,-0.000212 ,0.098828;
	CoM_URDF[4]<< 0.002354, -0.00032, 0.094781;
	CoM_URDF[5]<< 0 ,0.002249, 0.09774;
	CoM_URDF[6]<< 0.000084,-0.001022,0.00897;


	CoM[0] <<BASE_X+CoM_URDF[1](0),BASE_Y+CoM_URDF[1](1),BASE_Z+LINK_01+CoM_URDF[1](2);
	CoM[1] <<BASE_X+CoM_URDF[2](0),BASE_Y+CoM_URDF[2](1),BASE_Z+LINK_01+LINK_12+CoM_URDF[2](2);
	CoM[2] <<BASE_X+CoM_URDF[3](0),BASE_Y+CoM_URDF[3](1),BASE_Z+LINK_01+LINK_12+LINK_23+CoM_URDF[3](2);
	CoM[3] <<BASE_X+CoM_URDF[4](0),BASE_Y+CoM_URDF[4](1),BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+CoM_URDF[4](2);
	CoM[4] <<BASE_X+CoM_URDF[5](0),BASE_Y+CoM_URDF[5](1),BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45+CoM_URDF[5](2);
	CoM[5] <<BASE_X+CoM_URDF[6](0),BASE_Y+CoM_URDF[6](1),BASE_Z+LINK_01+LINK_12+LINK_23+LINK_34+LINK_45+LINK_56+CoM_URDF[6](2);

	inertia[0] << J_Ixx_1, J_Ixy_1, J_Ixz_1,
		J_Ixy_1, J_Iyy_1, J_Iyz_1,
		J_Ixz_1, J_Iyz_1, J_Izz_1;

	inertia[1] << J_Ixx_2, J_Ixy_2, J_Ixz_2,
		J_Ixy_2, J_Iyy_2, J_Iyz_2,
		J_Ixz_2, J_Iyz_2, J_Izz_2;

	inertia[2] << J_Ixx_3, J_Ixy_3, J_Ixz_3,
		J_Ixy_3, J_Iyy_3, J_Iyz_3,
		J_Ixz_3, J_Iyz_3, J_Izz_3;

	inertia[3] << J_Ixx_4, J_Ixy_4, J_Ixz_4,
		J_Ixy_4, J_Iyy_4, J_Iyz_4,
		J_Ixz_4, J_Iyz_4, J_Izz_4;

	inertia[4] << J_Ixx_5, J_Ixy_5, J_Ixz_5,
		J_Ixy_5, J_Iyy_5, J_Iyz_5,
		J_Ixz_5, J_Iyz_5, J_Izz_5;

	inertia[5] << J_Ixx_6, J_Ixy_6, J_Ixz_6,
		J_Ixy_6, J_Iyy_6, J_Iyz_6,
		J_Ixz_6, J_Iyz_6, J_Izz_6;




	//mass[0] = CoM[0].norm() / LINK_12 * MASS_1;
	//mass[1] = CoM[1].norm() / LINK_23 * MASS_2;
	//mass[2] = CoM[2].norm() / LINK_34 * MASS_3;
	//mass[3] = CoM[3].norm() / LINK_45 * MASS_4;
	//mass[4] = CoM[4].norm() / LINK_56 * MASS_5;
    mass[0] = MASS_1;
    mass[1] = MASS_2;
    mass[2] = MASS_3;
    mass[3] = MASS_4;
    mass[4] = MASS_5;
    mass[5] = MASS_6;

    for(int i=0; i<ROBOT_DOF; ++i)
    {
    	pDyn->UpdateDynamicInfo(inertia[i] , mass[i], i+1);
        pCoM->UpdateKinematicInfo_R(w[i], p[i], CoM[i],i+1);
    	pKin->UpdateKinematicInfo_R(w[i], p[i], L[i], i+1);
    }

}


void robot::motor_update_R(MOTOR_INFO *motor)
{
	motor->toq_const[0] = TORQUE_CONST_1;
	motor->toq_const[1] = TORQUE_CONST_2;
	motor->toq_const[2] = TORQUE_CONST_3;
	motor->toq_const[3] = TORQUE_CONST_4;
	motor->toq_const[4] = TORQUE_CONST_5;
	//motor->toq_const[5] = TORQUE_CONST_6;

	motor->gear_ratio[0] = HARMONIC_100;
	motor->gear_ratio[1] = HARMONIC_100;
	motor->gear_ratio[2] = HARMONIC_100;
	motor->gear_ratio[3] = HARMONIC_100;
	motor->gear_ratio[4] = HARMONIC_100;
	//motor->gear_ratio[5] = HARMONIC_100;
}

void robot::ENCtoRAD_R(int *enc, Jointf& q)   //may not use..
{
	for(int i=1; i<=ROBOT_DOF; ++i)
	{
		switch(i)
		{
		case 1:
			q(i-1) = -(float)(enc[i-1]/(4*ENC_1000))*2*M_PI/(float)HARMONIC_100;
			break;
		case 2:
			q(i-1) = -(float)(enc[i-1]/(4*ENC_1000))*2*M_PI/(float)HARMONIC_100 - M_PI/2;
			break;
		case 3:
			q(i-1) = -(float)(enc[i-1]/(4*ENC_1000))*2*M_PI/(float)HARMONIC_100;
			break;
		case 4:
			q(i-1) = (float)(enc[i-1]/(4*ENC_1000))*2*M_PI/(float)HARMONIC_100;
			break;
		case 5:
			q(i-1) = -(float)(enc[i-1]/(4*ENC_512))*2*M_PI/(float)HARMONIC_100;
			break;
//		case 6:
//			q(i-1) = (float)(enc[i-1]/(4*ENC_1024))*2*M_PI/(float)HARMONIC_100;
//			break;
		default:
			q(i-1) = (enc[i-1]/(4*ENC_1000))*2*M_PI/HARMONIC_100;
			break;
		}
	}
}

void robot::ENCtoRAD_R(int *enc, Jointf& q, Jointf& q_dot, float s_time)
{
	q_p = q;
	for(int i=1; i<=ROBOT_DOF; ++i)
	{
		switch(i)
		{
		case 1:
			q(i-1) = -(float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_1000*(float)HARMONIC_120);
			break;
		case 2:
			q(i-1) = -(float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_1000*(float)HARMONIC_120) - M_PI/2;
			break;
		case 3:
			q(i-1) = -(float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_1000*(float)HARMONIC_100);
			break;
		case 4:
			q(i-1) = (float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_1000*(float)HARMONIC_100);
			break;
		case 5:
			q(i-1) = (float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_512*(float)HARMONIC_50);
			break;
		case 6:
			q(i-1) = (float)enc[i-1]*2.0*M_PI/((float)4.0*ENC_1024*(float)HARMONIC_100);
			break;
		default:
			q(i-1) = (float)(enc[i-1]/(4*ENC_1000))*2*M_PI/HARMONIC_100;
			break;
		}
	}
	q_dot = (q - q_p)/s_time;
}

void robot::ELMO_OUTPUT_R(MOTOR_INFO *motor, Jointf& torque, short *output)
{
	for(int i=0; i<ROBOT_DOF; ++i)
	{
		switch(i+1)
		{
		case 1:
			if(abs(torque(i)/HARMONIC_120) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = -roundf(((torque(i)/HARMONIC_120)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = -sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		case 2:
			if(abs(torque(i)/HARMONIC_120) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = -roundf(((torque(i)/HARMONIC_120)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = -sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		case 3:
			if(abs(torque(i)/HARMONIC_100) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = -roundf(((torque(i)/HARMONIC_100)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = -sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		case 4:
			if(abs(torque(i)/HARMONIC_100) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = roundf(((torque(i)/HARMONIC_100)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		case 5:
			if(abs(torque(i)/HARMONIC_50) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = roundf(((torque(i)/HARMONIC_50)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		case 6:
			if(abs(torque(i)/HARMONIC_100) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = roundf(((torque(i)/HARMONIC_100)/motor->toq_const[i])/motor->rate_current[i]*1000*(100.0/EFFICIENCY));
			else
				output[i] = sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		default:
			if(abs(torque(i)/HARMONIC_100) <= motor->rate_current[i]*motor->toq_const[i]*1.2)
				output[i] = roundf(((torque(i)/HARMONIC_100)/motor->toq_const[i])/motor->rate_current[i]*1000);
			else
				output[i] = sign(torque(i))*MAX_CURRENT_ELMO;
			break;
		}
	}
}
