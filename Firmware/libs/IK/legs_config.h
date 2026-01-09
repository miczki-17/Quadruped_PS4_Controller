#ifndef LEGS_CONFIG_H
#define LEGS_CONFIG_H


#define LEGS_NUM 4

#define LEGLF 0
#define LEGRF 1
#define LEGLH 2
#define LEGRH 3



#define SERVO_MIN  800			// last value 800
#define SERVO_MAX 2450			// last value 2450



#define LEG_ANGLE_ALPHA 90
#define LEG_ANGLE_BETHA 90
#define LEG_ANGLE_GAMMA 90

#define LEG_ANGLE_ALPHA_MAX 180
#define LEG_ANGLE_ALPHA_MIN   0

#define LEG_ANGLE_BETHA_MAX 180
#define LEG_ANGLE_BETHA_MIN   0

#define LEG_ANGLE_GAMMA_MAX 180
#define LEG_ANGLE_GAMMA_MIN   0



#define LEG_SIZE_L1 33.15
#define LEG_SIZE_L2 60.04
#define LEG_SIZE_L3 85.00

#define LEG_BODY_X		35.89
#define LEG_BODY_Y_F	34.15
#define LEG_BODY_Y_H	34.15
#define LEG_BODY_Z		0.0

#define LEG_POINT_X		105.89		// + 70.0
#define LEG_POINT_Y_F	104.15		// + 70.0
#define LEG_POINT_Y_H	104.15
#define LEG_POINT_Z		70.00



leg legs[LEGS_NUM] = {

	// left front

	{
		{LEGLF},
		{
			4,
			2,
			15
		},
		{LEG_ANGLE_ALPHA, LEG_ANGLE_BETHA, LEG_ANGLE_GAMMA},
		{5, -15, -15},
		{LEG_SIZE_L1,		  LEG_SIZE_L2,		    LEG_SIZE_L3},
		{LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{LEG_POINT_X,		  LEG_POINT_Y_F,		LEG_POINT_Z},
		{-LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{0, 0, 0},
		{0, 0, 0},
		{false},
		{true, true, true, true, false, true}
	},



	// right front

	{
		{LEGRF},
		{
			14,
			12,
			13
		},
		{LEG_ANGLE_ALPHA, LEG_ANGLE_BETHA, LEG_ANGLE_GAMMA},
		{-20, -20, 0},
		{LEG_SIZE_L1,		  LEG_SIZE_L2,		    LEG_SIZE_L3},
		{LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{LEG_POINT_X,		  LEG_POINT_Y_F,		LEG_POINT_Z},
		{LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{0, 0, 0},
		{0, 0, 0},
		{false},
		{false, false, false, false, false, true}
	},



	// left hind

	{
		{LEGLH},
		{
			33,
			32,
			23
		},
		{LEG_ANGLE_ALPHA, LEG_ANGLE_BETHA, LEG_ANGLE_GAMMA},
		{-30, -30, -10},
		{LEG_SIZE_L1,		  LEG_SIZE_L2,		    LEG_SIZE_L3},
		{LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{LEG_POINT_X,		  LEG_POINT_Y_F,		LEG_POINT_Z},
		{-LEG_BODY_X,		  -LEG_BODY_Y_F,		LEG_BODY_Z},
		{0, 0, 0},
		{0, 0, 0},
		{false},
		{false, false, false, true, true, true}
	},



	// right hind

	{
		{LEGRH},
		{
			27,
			26,
			25
		},
		{LEG_ANGLE_ALPHA, LEG_ANGLE_BETHA, LEG_ANGLE_GAMMA},
		{-5, -15, -15},
		{LEG_SIZE_L1,		  LEG_SIZE_L2,		    LEG_SIZE_L3},
		{LEG_BODY_X,		  LEG_BODY_Y_F,			LEG_BODY_Z},
		{LEG_POINT_X,		  LEG_POINT_Y_F,		LEG_POINT_Z},
		{LEG_BODY_X,		  -LEG_BODY_Y_F,		LEG_BODY_Z},
		{0, 0, 0},
		{0, 0, 0},
		{false},
		{true, true, true, false, true, true}
	},
};


#endif
