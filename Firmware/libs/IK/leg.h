#ifndef LEG_H
#define LEG_H


typedef struct {
	int id;
} legId;

typedef struct {
	int alpha;
	int beta;
	int gamma;
} legPin;

typedef struct {
	double alpha;
	double beta;
	double gamma;
} legAngle;

typedef struct {
	double l1;
	double l2;
	double l3;
} legSize;

typedef struct {
	double x;
	double y;
	double z;
} point;

typedef struct {
	bool onGround;
} legSensor;

typedef struct {
	bool alpha;
	bool beta;
	bool gamma;
	bool x;
	bool y;
	bool z;
} legInverse;

typedef struct {
	legId		id;
	legPin		pin;
	legAngle	angle;
	legAngle	angledefect;
	legSize		size;
	point		defaultbody;
	point		defaultfoot;
	point		realbody;
	point		realfoot;
	point		foorgyro;
	legSensor	sensor;
	legInverse  inverse;
} leg;


#endif
