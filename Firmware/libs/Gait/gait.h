#ifndef GAIT_H
#define GAIT_H


#include "../IK/leg.h"
#include "../IK/geometry.h"



#define DIR_NUM  4


#define RIGHT	 0
#define LEFT	 1
#define STRAIGHT 2
#define BACK	 3

#define WAIT	 4


#define RIGHT_ROTATION 5
#define LEFT_ROTATION  6




#define GAIT_LEG_DISTANCE 40
#define GAIT_LEG_UP   22			// prev 18
#define GAIT_LEG_DOWN 22			// prev18

#define GAIT_LEG_RIGHT_ROTATION_DISTANCE 40
#define GAIT_LEG_LEFT_ROTATION_DISTANCE  40


#define Z_HOP_MAX 115		// prev 105
#define Z_HOP_MIN  40		// prev -20



#define STEP0 0x00000000
#define STEP1 0x00000001
#define STEP2 0x00000010
#define STEP3 0x00000100
#define STEP4 0x00001000
#define STEP5 0x00010000
#define STEP6 0x00100000


// analog steps

#define STEP0_ANALOG 0x00000000
#define STEP1_ANALOG 0x00000001
#define STEP2_ANALOG 0x00000010

// analog distance

#define GAIT_LEG_DISTANCE_ANALOG 40
#define GAIT_LEG_UP_ANALOG		 18
#define GAIT_LEG_DOWN_ANALOG	 18



typedef struct {
	int16_t right;
	int16_t left;
	int16_t straight;
	int16_t back;
	int16_t right_rotation;
	int16_t left_rotation;
} direction_step;

direction_step step{
	0x01,
	0x01,
	0x01,
	0x01,
	0x01,
	0x01
};




typedef struct {
	const double speed_10;
	const double speed_20;
	const double speed_30;
	const double speed_40;
	const double speed_50;
	const double speed_60;
} speed_table;

speed_table speed{
	10,
	20,
	30,
	40,
	50,
	60
};




class Gait {
	public:
		Gait(leg* legs, figure& bodyObj);
		~Gait();

		int8_t getStep();
		
		void move();
		void setDirection(const int8_t direction);

		void attackMove();



		// analog moving

		void analogMove(int x, int y);


	private:
		leg* _legs;
		figure* _body;

		int8_t direction;

		void nextStep();


		bool isCenterOfMass;
		void calculateCenterOfMass();



		double speedTime;
		void calculateSpeed();



		// analog moving is using left control pad
		int8_t current_analog_step = STEP1_ANALOG;

		void analogNextStep();
		
};


#endif
