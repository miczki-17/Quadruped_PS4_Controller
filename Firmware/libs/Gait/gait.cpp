#include "gait2.h"
#include <math.h>

#define PI 3.14159265359f

Gait2::Gait2(leg* legs, figure& body) {
    _legs = legs;
    _body = &body;
}

void Gait2::resetToDefault() {
    for (int i = 0; i < 4; i++) {
        _legs[i].realfoot = _legs[i].defaultfoot;
    }
}

void Gait2::setVelocity(float vx, float vy) {
    _vx = vx;
    _vy = vy;
}

void Gait2::setVelocity(float vx, float vy, float omega) {
    _vx = vx;
    _vy = vy;
    _omega = omega;
}

void Gait2::update(float dt) {

    // Low-pass filtering of velocity
    _filteredVx += _alphaFilter * (_vx - _filteredVx);
    _filteredVy += _alphaFilter * (_vy - _filteredVy);

    _filteredOmega += _alphaFilter * (_omega - _filteredOmega);
    _yaw += _filteredOmega * dt;

    float velocityMagnitude = sqrt(_filteredVx * _filteredVx + _filteredVy * _filteredVy);
    float motionMagnitude = velocityMagnitude + abs(_filteredOmega * 10.0f);

    // Deadband - the robot stops when motion is below the threshold
    if (motionMagnitude < 0.1f) {
        resetToDefault();
        return;
    }

    // --- 1. VELOCITY RATIO SCALING ---
    float translationRatio = velocityMagnitude / _maxVelocity;
    float rotationRatio = abs(_filteredOmega) / _maxOmega;

    float speedRatio = translationRatio + rotationRatio;
    if (speedRatio > 1.0f) {
        speedRatio = 1.0f;
    }

    // --- 2. FILTERED STEP HEIGHT ---
    _targetStepHeight = _minStepHeight + (_maxStepHeight - _minStepHeight) * speedRatio;
    _currentStepHeight += _stepHeightAlpha * (_targetStepHeight - _currentStepHeight);

    // --- 3. DYNAMIC STEP FREQUENCY ---
    _currentStepFrequency = _minStepFrequency + (_maxStepFrequency - _minStepFrequency) * speedRatio;

    // --- 4. DYNAMIC BODY DROP ---
    _currentBodyDrop = _maxBodyDrop * speedRatio;


    // --- PHASE AND STEP UPDATE ---
    float stepLength = velocityMagnitude / _currentStepFrequency;

    _phase += dt * _currentStepFrequency;

    if (_phase > 1.0f)
        _phase -= 1.0f;

    for (int i = 0; i < 4; i++) {
        float legPhase = _phase + legPhaseOffset[i];
        if (legPhase > 1.0f)
            legPhase -= 1.0f;

        computeFootTrajectory(i, legPhase);
    }
}

void Gait2::computeFootTrajectory(int legIndex, float phase)
{
    // 1. Base foot position (R vector from the robot's center)
    float footBaseX = _legs[legIndex].defaultfoot.x;
    float footBaseY = _legs[legIndex].defaultfoot.y;

    // 2. Velocity vector for THIS SPECIFIC FOOT
    float v_foot_x = _filteredVx + (_filteredOmega * footBaseY * rotationGain);
    float v_foot_y = _filteredVy - (_filteredOmega * footBaseX * rotationGain);

    // 3. Calculation of step length for this foot using DYNAMIC frequency
    float stepLengthX = v_foot_x / _currentStepFrequency;
    float stepLengthY = v_foot_y / _currentStepFrequency;

    // 4. Step parameters
    float moveX = 0.0f;
    float moveY = 0.0f;
    float dz = 0.0f;

    // STANCE / SWING
    if (phase < 0.5f)
    {
        // STANCE (foot on the ground)
        float t = phase / 0.5f;     // 0 -> 1
        moveX = -stepLengthX * (t - 0.5f);
        moveY = -stepLengthY * (t - 0.5f);
        dz = 0.0f;
    }
    else
    {
        // SWING (foot in the air)
        float t = (phase - 0.5f) / 0.5f;   // 0 -> 1
        moveX = stepLengthX * (t - 0.5f);
        moveY = stepLengthY * (t - 0.5f);

        // Lifting the foot along a sinusoid - using VARIABLE height
        dz = _currentStepHeight * sin(t * PI);
    }

    float finalMoveX = moveX;
    float finalMoveY = moveY;

    // 5. BODY LEAN CALCULATION (PITCH & ROLL)
    // Offset depends on the velocity on a given axis and the physical position of the foot relative to the center
    float pitchOffset = footBaseX * (_filteredVx / _maxVelocity) * _pitchMultiplier;
    float rollOffset = footBaseY * (_filteredVy / _maxVelocity) * _rollMultiplier;

    // 6. FINAL FOOT POSITION
    _legs[legIndex].realfoot.x = footBaseX + finalMoveX;
    _legs[legIndex].realfoot.y = footBaseY + finalMoveY;

    // Z-Offset: 
    // Add step height (dz) 
    // Add body drop (BodyDrop) 
    // Add lean on the respective axes (pitch/roll)
    _legs[legIndex].realfoot.z = _legs[legIndex].defaultfoot.z + dz + _currentBodyDrop + pitchOffset + rollOffset;
}
