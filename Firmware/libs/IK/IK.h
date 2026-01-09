#ifndef IK_H
#define IK_H


#include "geometry.h"
#include "leg.h"


typedef struct {
	bool isSolved;
	legAngle angle;
} iksolver;


class IK {
	public:
		IK(leg& _legObj, figure& _bodyObj);

		void set(leg& _legObj, figure& _bodyObj);

		iksolver solve();



	private:
		leg* _leg;
		figure* _body;

		double ikAtan2(double x, double y);
		double ikAtan(double angleRad);
		double ikAcos(double angleRad);
		double ikAsin(double angleRad);

};

#endif // IK_H
