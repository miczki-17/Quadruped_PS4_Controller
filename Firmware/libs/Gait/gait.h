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
    // --- PARAMETRY PR?DKO?CI ---
    // ==========================================
    const float _maxVelocity = 150.0f;  // mm/s
    const float _maxOmega = 3.0f;       // rad/s (maksymalna predkosc obrotu z pada)
    const float _alphaFilter = 0.1f;    // Filtr LPF dla wektorów ruchu

    // ==========================================
    // --- DYNAMICZNA CZ?STOTLIWO?? KROKU ---
    // ==========================================
    float _currentStepFrequency = 2.2f; // Aktualna cz?stotliwosc (Hz)
    float _minStepFrequency = 1.5f;     // Wolny krok przy starcie
    float _maxStepFrequency = 3.0f;     // Szybki klus przy max predkosci

    // ==========================================
    // --- DYNAMICZNA WYSOKO?? KROKU ---
    // ==========================================
    float _maxStepHeight = 38.0f;       // Maksymalna wysokosc podniesienia nogi
    float _minStepHeight = 18.0f;       // Minimalna wysokosc (zeby nie szural)
    float _targetStepHeight = 0.0f;
    float _currentStepHeight = 0.0f;
    float _stepHeightAlpha = 0.08f;     // Plynnosc zmiany wysokosci nogi

    // ==========================================
    // --- OBNI?ANIE TU?OWIA (COMBAT STANCE) ---
    // ==========================================
    float _maxBodyDrop = 5.0f;         // Max obnizenie tulowia w mm przy pelnej predkosci
    float _currentBodyDrop = 0.0f;

    // ==========================================
    // --- POCHYLANIE (PITCH & ROLL LEAN) ---
    // ==========================================
    float _pitchMultiplier = 0.0f;     // Wspólczynnik pochylania przod/tyl?
    float _rollMultiplier = 0.0f;      // Wspólczynnik pochylania na boki

    float _omega = 0.0f;
    float _filteredOmega = 0.0f;
    float _yaw = 0.0f;

    float rotationGain = 1.5f;

    float legPhaseOffset[4] = {
        0.0f,   // LF
        0.5f,   // RF
        0.5f,   // LH
        0.0f    // RH
    };

    void computeFootTrajectory(int legIndex, float legPhase);
};

#endif
