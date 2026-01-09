#ifndef GEOMETRY_H
#define GEOMETRY_H


#define ALPHA 0
#define BETA  1
#define GAMMA 2


#define XAXIS     0
#define YAXIS     1
#define ZAXIS     2
#define PITCHAXIS 3
#define ROLLAXIS  4
#define YAWAXIS   5


// pount in 3D
typedef struct {
	double x;
	double y;
	double z;
} point3d;

// angle in 3D
typedef struct {
	double roll;    // X axis
	double pitch;   // Y axis
	double yaw;     // Z axis
} angle3d;

//body
typedef struct {
	point3d position;
	angle3d orientation;
} figure;

//move
typedef struct {
	point3d move;
	angle3d rotate;
} moveVector;


#endif // GEOMETRY_H
