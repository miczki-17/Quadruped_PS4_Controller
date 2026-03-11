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

    // Low-pass filtering predkosci
    _filteredVx += _alphaFilter * (_vx - _filteredVx);
    _filteredVy += _alphaFilter * (_vy - _filteredVy);

    _filteredOmega += _alphaFilter * (_omega - _filteredOmega);
    _yaw += _filteredOmega * dt;

    float velocityMagnitude = sqrt(_filteredVx * _filteredVx + _filteredVy * _filteredVy);
    float motionMagnitude = velocityMagnitude + abs(_filteredOmega * 10.0f);

    // Deadband - robot staje, gdy ruch jest ponizej progu
    if (motionMagnitude < 0.1f) {
        resetToDefault();
        return;
    }

    // --- 1. SKALOWANIE WSPOLCZYNNIKA PREDKOSCI ---
    float translationRatio = velocityMagnitude / _maxVelocity;
    float rotationRatio = abs(_filteredOmega) / _maxOmega;

    float speedRatio = translationRatio + rotationRatio;
    if (speedRatio > 1.0f) {
        speedRatio = 1.0f;
    }

    // --- 2. FILTROWANA WYSOKOSC KROKU ---
    _targetStepHeight = _minStepHeight + (_maxStepHeight - _minStepHeight) * speedRatio;
    _currentStepHeight += _stepHeightAlpha * (_targetStepHeight - _currentStepHeight);

    // --- 3. DYNAMICZNA CZESTOTLIWOSC KROKU ---
    _currentStepFrequency = _minStepFrequency + (_maxStepFrequency - _minStepFrequency) * speedRatio;

    // --- 4. DYNAMICZNE OBNIZANIE TULOWIA ---
    _currentBodyDrop = _maxBodyDrop * speedRatio;


    // --- AKTUALIZACJA FAZY I KROKU ---
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
    // 1. Pozycja bazowa stopy (wektor R od ?rodka robota)
    float footBaseX = _legs[legIndex].defaultfoot.x;
    float footBaseY = _legs[legIndex].defaultfoot.y;

    // 2. Wektor pr?dko?ci dla TEJ KONKRETNEJ STOPY
    float v_foot_x = _filteredVx + (_filteredOmega * footBaseY * rotationGain);
    float v_foot_y = _filteredVy - (_filteredOmega * footBaseX * rotationGain);

    // 3. Obliczenie d?ugo?ci kroku dla tej stopy z u?yciem DYNAMICZNEJ cz?stotliwo?ci
    float stepLengthX = v_foot_x / _currentStepFrequency;
    float stepLengthY = v_foot_y / _currentStepFrequency;

    // 4. Parametry kroku
    float moveX = 0.0f;
    float moveY = 0.0f;
    float dz = 0.0f;

    // STANCE / SWING
    if (phase < 0.5f)
    {
        // STANCE (noga na ziemi)
        float t = phase / 0.5f;     // 0 -> 1
        moveX = -stepLengthX * (t - 0.5f);
        moveY = -stepLengthY * (t - 0.5f);
        dz = 0.0f;
    }
    else
    {
        // SWING (noga w powietrzu)
        float t = (phase - 0.5f) / 0.5f;   // 0 -> 1
        moveX = stepLengthX * (t - 0.5f);
        moveY = stepLengthY * (t - 0.5f);

        // podnoszenie nogi po sinusoidzie - uzywamy ZMIENNEJ wysoko?ci
        dz = _currentStepHeight * sin(t * PI);
    }

    float finalMoveX = moveX;
    float finalMoveY = moveY;

    // 5. OBLICZANIE POCHYLENIA TULOWIA (PITCH & ROLL)
    // Offset uzalezniamy od predkosci na danej osi i fizycznego polozenia nogi wzgledem srodka
    float pitchOffset = footBaseX * (_filteredVx / _maxVelocity) * _pitchMultiplier;
    float rollOffset = footBaseY * (_filteredVy / _maxVelocity) * _rollMultiplier;

    // 6. FINALNA POZYCJA STOPY
    _legs[legIndex].realfoot.x = footBaseX + finalMoveX;
    _legs[legIndex].realfoot.y = footBaseY + finalMoveY;

    // Z-Offset: 
    // Dodajemy wysokosc kroczenia (dz) 
    // Dodajemy obni?anie tulowia (BodyDrop) 
    // Dodajemy pochylenie na odpowiednich osiach (pitch/roll)
    _legs[legIndex].realfoot.z = _legs[legIndex].defaultfoot.z + dz + _currentBodyDrop + pitchOffset + rollOffset;
}
