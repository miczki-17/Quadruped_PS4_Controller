#include "gait.h"

#include "math.h"

#define RAD_TO_DEG (180 / 3.14159)


Gait::Gait(leg* legs, figure& bodyObj) {
	_legs = legs;
	_body = &bodyObj;

	direction = WAIT;
}

Gait::~Gait() {
	
}





void Gait::nextStep() {
	switch (this->direction) {
	case STRAIGHT:
		if (step.straight == STEP2) {
			step.straight = STEP1;
			break;
		}
		step.straight <<= 0x01;
		break;
	case RIGHT:
		if (step.right == STEP2) {
			step.right = STEP1;
			break;
		}
		step.right <<= 0x01;
		break;
	case LEFT:
		if (step.left == STEP2) {
			step.left = STEP1;
			break;
		}
		step.left <<= 0x01;
		break;
	case BACK:
		if (step.back == STEP2) {
			step.back = STEP1;
			break;
		}
		step.back <<= 0x01;
		break;
	case RIGHT_ROTATION:
		/*if (step.right_rotation == STEP2) {
			step.right_rotation = STEP1;
			break;
		}
		step.right_rotation <<= 0x01;*/
		break;
	case LEFT_ROTATION:
		/*if (step.left_rotation == STEP2) {
			step.left_rotation == STEP1;
			break;
		}
		step.left_rotation <<= 0x01;*/
		break;
	default:
		break;
	}
}


// analog

void Gait::analogNextStep() {
	if (this->current_analog_step == STEP1)
		current_analog_step = STEP2;
	else
		current_analog_step = STEP1;
}









void Gait::setDirection(const int8_t direction) {
	this->direction = direction;
}


void Gait::move() {
	switch (this->direction) {
	case STRAIGHT:
		switch (step.straight) {
		case STEP1:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.y++;
				legs[LEGLH].realfoot.y++;
				legs[LEGRH].realfoot.y--;
				legs[LEGLF].realfoot.y--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.y++;
				legs[LEGRH].realfoot.y++;
				legs[LEGLH].realfoot.y--;
				legs[LEGRF].realfoot.y--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}
			break;
		case STEP2:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.y++;
				legs[LEGRH].realfoot.y++;
				legs[LEGLH].realfoot.y--;
				legs[LEGRF].realfoot.y--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.y++;
				legs[LEGLH].realfoot.y++;
				legs[LEGRH].realfoot.y--;
				legs[LEGLF].realfoot.y--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}
			break;
		default:
			break;
		}
		break;




	case RIGHT:
		switch (step.right) {
		case STEP1:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.x++;
				legs[LEGLH].realfoot.x++;
				legs[LEGRH].realfoot.x--;
				legs[LEGLF].realfoot.x--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.x++;
				legs[LEGRH].realfoot.x++;
				legs[LEGLH].realfoot.x--;
				legs[LEGRF].realfoot.x--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}
			break;
		case STEP2:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.x++;
				legs[LEGRH].realfoot.x++;
				legs[LEGLH].realfoot.x--;
				legs[LEGRF].realfoot.x--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.x++;
				legs[LEGLH].realfoot.x++;
				legs[LEGRH].realfoot.x--;
				legs[LEGLF].realfoot.x--;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}
			break;
		default:
			break;
		}
		break;





	case LEFT:
		switch (step.left) {
		case STEP1:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.x--;
				legs[LEGLH].realfoot.x--;
				legs[LEGRH].realfoot.x++;
				legs[LEGLF].realfoot.x++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.x--;
				legs[LEGRH].realfoot.x--;
				legs[LEGLH].realfoot.x++;
				legs[LEGRF].realfoot.x++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}
			break;
		case STEP2:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.x--;
				legs[LEGRH].realfoot.x--;
				legs[LEGLH].realfoot.x++;
				legs[LEGRF].realfoot.x++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.x--;
				legs[LEGLH].realfoot.x--;
				legs[LEGRH].realfoot.x++;
				legs[LEGLF].realfoot.x++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}
			break;
		}
		break;




	case BACK:
		switch (step.back) {
		case STEP1:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.y--;
				legs[LEGLH].realfoot.y--;
				legs[LEGRH].realfoot.y++;
				legs[LEGLF].realfoot.y++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.y--;
				legs[LEGRH].realfoot.y--;
				legs[LEGLH].realfoot.y++;
				legs[LEGRF].realfoot.y++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}
			break;
		case STEP2:
			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGLF].realfoot.z++;
				legs[LEGRH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGLF].realfoot.y--;
				legs[LEGRH].realfoot.y--;
				legs[LEGLH].realfoot.y++;
				legs[LEGRF].realfoot.y++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGLF].realfoot.z--;
				legs[LEGRH].realfoot.z--;
				delay(1);
			}

			for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
				legs[LEGRF].realfoot.z++;
				legs[LEGLH].realfoot.z++;
				delay(1);
			}
			for (int8_t i = 0; i < GAIT_LEG_DISTANCE; i++) {
				legs[LEGRF].realfoot.y--;
				legs[LEGLH].realfoot.y--;
				legs[LEGRH].realfoot.y++;
				legs[LEGLF].realfoot.y++;
				delay(2);
			}
			for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
				legs[LEGRF].realfoot.z--;
				legs[LEGLH].realfoot.z--;
				delay(1);
			}
			break;
		}
		break;

	case RIGHT_ROTATION:
		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGRF].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGRF].realfoot.x++;
			legs[LEGRF].realfoot.y--;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGRF].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGLF].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGLF].realfoot.x++;
			legs[LEGLF].realfoot.y++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGLF].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGRH].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGRH].realfoot.x--;
			legs[LEGRH].realfoot.y--;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGRH].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGLH].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGLH].realfoot.x--;
			legs[LEGLH].realfoot.y++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGLH].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGRF].realfoot.x--;
			legs[LEGRF].realfoot.y++;

			legs[LEGLF].realfoot.x--;
			legs[LEGLF].realfoot.y--;

			legs[LEGRH].realfoot.x++;
			legs[LEGRH].realfoot.y++;

			legs[LEGLH].realfoot.x++;
			legs[LEGLH].realfoot.y--;

			delay(1);
		}
		break;



	case LEFT_ROTATION:
		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGRF].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_LEFT_ROTATION_DISTANCE; i++) {
			legs[LEGRF].realfoot.x--;
			legs[LEGRF].realfoot.y++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGRF].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGLF].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_LEFT_ROTATION_DISTANCE; i++) {
			legs[LEGLF].realfoot.x--;
			legs[LEGLF].realfoot.y--;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGLF].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGRH].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_LEFT_ROTATION_DISTANCE; i++) {
			legs[LEGRH].realfoot.x++;
			legs[LEGRH].realfoot.y++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGRH].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_UP; i++) {
			legs[LEGLH].realfoot.z++;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_LEFT_ROTATION_DISTANCE; i++) {
			legs[LEGLH].realfoot.x++;
			legs[LEGLH].realfoot.y--;
			delay(1);
		}
		for (int8_t i = 0; i < GAIT_LEG_DOWN; i++) {
			legs[LEGLH].realfoot.z--;
			delay(1);
		}


		for (int8_t i = 0; i < GAIT_LEG_RIGHT_ROTATION_DISTANCE; i++) {
			legs[LEGRF].realfoot.x++;
			legs[LEGRF].realfoot.y--;

			legs[LEGLF].realfoot.x++;
			legs[LEGLF].realfoot.y++;

			legs[LEGRH].realfoot.x--;
			legs[LEGRH].realfoot.y--;

			legs[LEGLH].realfoot.x--;
			legs[LEGLH].realfoot.y++;

			delay(1);
		}
		break;
	}

	this->nextStep();
}

void Gait::attackMove(void) {
	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x--;
		this->_body->position.y--;
		delay(8);
	}
	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x++;
		this->_body->position.y++;
		delay(8);
	}

	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x++;
		this->_body->position.y++;
		delay(8);
	}
	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x--;
		this->_body->position.y--;
		delay(8);
	}

	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x++;
		this->_body->position.y--;
		delay(8);
	}
	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x--;
		this->_body->position.y++;
		delay(8);
	}

	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x--;
		this->_body->position.y++;
		delay(8);
	}
	for (int8_t i = 0; i < 40; i++) {
		this->_body->position.x++;
		this->_body->position.y--;
		delay(8);
	}
}





// analog move

void Gait::analogMove(int x, int y) {

	double alpha = atan(static_cast<double>(y) / x);

	double x_trim = 40 * cos(alpha);
	double y_trim = 40 * sin(alpha);

	switch (this->current_analog_step) {
	case STEP1_ANALOG:
		
		break;

	case STEP2_ANALOG:
		
		break;

	default:
		break;
	}

	this->analogNextStep();
}









void Gait::calculateCenterOfMass() {
	
}







int8_t Gait::getStep() {
	return 0;
}
