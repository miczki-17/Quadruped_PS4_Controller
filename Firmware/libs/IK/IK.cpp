#include "IK.h"
#include "leg.h"

#include "math.h"


#define RAD_TO_DEG (180 / 3.14159)
#define DEG_TO_RAD (3.14159 / 180)


// constructors & destructors

IK::IK(leg& _legObj, figure& _bodyObj) {
	_leg = &_legObj;
	_body = &_bodyObj;
}




// public methods

void IK::set(leg& _legObj, figure& _bodyObj) {
	_leg = &_legObj;
	_body = &_bodyObj;
}




// IK solve

iksolver IK::solve() {
	iksolver s;
	legAngle angle;



	// get roll, pitch and yaw trim

	double H_roll = _leg->realbody.y;
	double lz_body_trim_roll = H_roll * sin(_body->orientation.roll * DEG_TO_RAD);
	double ly_body_trim_roll = H_roll * cos(_body->orientation.roll * DEG_TO_RAD);

	double H_pitch = _leg->realbody.x;
	double lz_body_trim_pitch = H_pitch * sin(_body->orientation.pitch * DEG_TO_RAD);
	double lx_body_trim_pitch = H_pitch * cos(_body->orientation.pitch * DEG_TO_RAD);

	double H_yaw = _leg->realbody.x;
	double lx_body_trim_yaw = H_yaw * cos(_body->orientation.yaw * DEG_TO_RAD);
	double ly_body_trim_yaw = H_yaw * sin(_body->orientation.yaw * DEG_TO_RAD);




	point l_trim{
		(_leg->realbody.x - lx_body_trim_pitch) - (_leg->realbody.x - lx_body_trim_yaw),
		(_leg->realbody.y - ly_body_trim_roll) - ly_body_trim_yaw,
		lz_body_trim_roll + lz_body_trim_pitch
	};


	double lx = _leg->realfoot.x - _body->position.x - l_trim.x; if (_leg->inverse.x) { lx = -lx; }
	double ly = _leg->realfoot.y - _body->position.y - l_trim.y; if (_leg->inverse.y) { ly = -ly; }
	double lz = _leg->realfoot.z - _body->position.z + l_trim.z; if (_leg->inverse.z) { lz = -lz; }



	// x y cartesian
	double A1 = ikAtan(ly / lx);

	double lx_trim = cos(A1) * _leg->size.l1;
	double ly_trim = sin(A1) * _leg->size.l1;
	
	lx -= lx_trim;
	ly -= ly_trim;

	double C = sqrt(lx * lx + ly * ly);

	double J1 = A1;



	// c z cartesian
	double A2 = ikAtan(lz / C);
	double L = sqrt(C * C + lz * lz);

	double B = ikAcos((L * L + _leg->size.l2 * _leg->size.l2 - _leg->size.l3 * _leg->size.l3) / (2 * L * _leg->size.l2));
	double J2 = B - A2;

	double J3 = ikAcos((_leg->size.l2 * _leg->size.l2 + _leg->size.l3 * _leg->size.l3 - L * L) / (2 * _leg->size.l2 * _leg->size.l3));



	double tmp_values[] = { J1, J2, J3 };

	for (int8_t i = 0; i < sizeof(tmp_values) / sizeof(double); i++) {
		if (tmp_values[i] != tmp_values[i]) {
			s.isSolved = false;
			return s;
		}
	}

	s.isSolved = true;


	
	if (_leg->inverse.alpha)
		angle.alpha = M_PI - (M_PI_2 + J1);
	else
		angle.alpha = M_PI_2 + J1;

	if (_leg->inverse.beta)
		angle.beta = (M_PI - (M_PI_2 + J2));
	else
		angle.beta = (M_PI_2 + J2);

	if (_leg->inverse.gamma)
		angle.gamma = M_PI - (M_PI - J3);
	else
		angle.gamma = M_PI - J3;



	s.angle = angle;

	return s;
}




// private methods

double IK::ikAtan2(double x, double y) {
	return atan2(x, y);
}

double IK::ikAtan(double angleRad) {
	return atan(angleRad);
}

double IK::ikAcos(double angleRad) {
	return acos(angleRad);
}

double IK::ikAsin(double angleRad) {
	return asin(angleRad);
}
