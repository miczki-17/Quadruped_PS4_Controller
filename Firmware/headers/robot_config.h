#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// Configuration for rotation origin and body offsets
// If ROTATION_ORIGIN_USE_DEFAULTBODY is 1, IK rotations (roll/pitch/yaw) are computed
// around the leg's default body attachment point (recommended). If 0, the code will
// use the leg->realbody values (original behavior).
#define ROTATION_ORIGIN_USE_DEFAULTBODY 1

// Body center offset (in mm) relative to robot coordinate frame. Useful if the
// physical center of mass / rotation is not at (0,0,0).
#define BODY_CENTER_OFFSET_X 0.0
#define BODY_CENTER_OFFSET_Y 0.0
#define BODY_CENTER_OFFSET_Z 0.0

#endif // ROBOT_CONFIG_H
