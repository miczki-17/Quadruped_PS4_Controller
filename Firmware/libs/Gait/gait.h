#ifndef GAIT2_H
#define GAIT2_H

#include "../IK/leg.h"
#include "../IK/geometry.h"

class Gait2 {
public:
    Gait2(leg* legs, figure& body);

    void update(float dt);
    void setVelocity(float vx, float vy);
    void setVelocity(float vx, float vy, float omega);
    void resetToDefault();

private:
    leg* _legs;
    figure* _body;

    float _vx = 0.0f;
    float _vy = 0.0f;

    float _filteredVx = 0.0f;
    float _filteredVy = 0.0f;

    float _phase = 0.0f;

    // ==========================================
    // --- VELOCITY PARAMETERS ---
    // ==========================================
    const float _maxVelocity = 150.0f;  // mm/s
    const float _maxOmega = 3.0f;       // rad/s (maximum rotation speed from gamepad)
    const float _alphaFilter = 0.1f;    // Low-Pass Filter (LPF) for motion vectors

    // ==========================================
    // --- DYNAMIC STEP FREQUENCY ---
    // ==========================================
    float _currentStepFrequency = 2.2f; // Current frequency (Hz)
    float _minStepFrequency = 1.5f;     // Slow step at startup
    float _maxStepFrequency = 3.0f;     // Fast trot at max speed

    // ==========================================
    // --- DYNAMIC STEP HEIGHT ---
    // ==========================================
    float _maxStepHeight = 38.0f;       // Maximum leg lift height
    float _minStepHeight = 18.0f;       // Minimum height (to prevent dragging)
    float _targetStepHeight = 0.0f;
    float _currentStepHeight = 0.0f;
    float _stepHeightAlpha = 0.08f;     // Smoothness of leg height change

    // ==========================================
    // --- BODY DROP (COMBAT STANCE) ---
    // ==========================================
    float _maxBodyDrop = 5.0f;         // Max body drop in mm at full speed
    float _currentBodyDrop = 0.0f;

    // ==========================================
    // --- BODY LEAN (PITCH & ROLL) ---
    // ==========================================
    float _pitchMultiplier = 0.0f;     // Forward/backward lean multiplier
    float _rollMultiplier = 0.0f;      // Sideways lean multiplier

    float _omega = 0.0f;
    float _filteredOmega = 0.0f;
    float _yaw = 0.0f;

    float rotationGain = 1.5f;

    float legPhaseOffset[4] = {
        0.0f,   // LF (Left Front)
        0.5f,   // RF (Right Front)
        0.5f,   // LH (Left Hind)
        0.0f    // RH (Right Hind)
    };

    void computeFootTrajectory(int legIndex, float legPhase);
};

#endif
