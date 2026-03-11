#include "headers/uc_config.h"
#include "headers/controller_config.h"

#include "libs/IK/leg.h"
#include "libs/IK/legs_config.h"
#include "libs/IK/geometry.h"
#include "libs/IK/IK.h"
#include "libs/IK/IK.cpp"

#include "libs/Gait/gait2.h"
#include "libs/Gait/gait2.cpp"

#if PWM_CONTROLLER == ESP32
#include <ESP32_ISR_Servo.h>
#endif

#include <Bluepad32.h>

// ==========================================
//           MPU6050 CONFIGURATION
// ==========================================
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

// PARAMETRY DO REGULACJI:
float mpuAlpha = 0.05f;            // LPF filter factor
float mpuCompensationGain = -1.6f; // force and direction of compensation

float targetPitch = 0.0f;
float targetRoll = 0.0f;
float currentPitch = 0.0f;
float currentRoll = 0.0f;
bool mpuReady = false;             // IS MPU Ready?
// ==========================================

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

figure body = {
  {0, 0, 0},
  {0, 0, 0}
};

Gait2 gait(legs, body);

IK ikLegLF(legs[LEGLF], body);
IK ikLegRF(legs[LEGRF], body);
IK ikLegLH(legs[LEGLH], body);
IK ikLegRH(legs[LEGRH], body);

iksolver legSolve[LEGS_NUM];

TaskHandle_t ServiceTask;

typedef unsigned long ul;

ul currentMicros;
ul lastMicros = 0;
ul elapsedMicros;

ul serviceCurrentMicros;
ul serviceLastMicros = 0;
ul serviceElapsedMicros;

bool mainLoopIsReady = false;
bool serviceLoopIsReady = false;
bool isControllerConnected = false;

void setup() {
#ifdef BAUD
  Serial.begin(115200);
#endif

#ifdef RANDOM_SEED_CONTROLLER
  randomSeed(analogRead(RANDOM_SEED_PIN));
#endif

#ifdef BAUD
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
#endif

  // MPU6050 start without calibration
  // ------------------------------------
  Wire.begin();
  byte status = mpu.begin();
#ifdef BAUD
  if (status == 0) {
    Serial.println(F("MPU6050 podlaczone. Czekam na pada, zeby wstanac..."));
  } else {
    Serial.print(F("Blad komunikacji MPU6050: "));
    Serial.println(status);
  }
#endif
  // ------------------------------------

  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.enableVirtualDevice(false);
  initServos();

  xTaskCreatePinnedToCore(
    serviceLoop,
    "service",
    8192,
    NULL,
    0,
    &ServiceTask,
    0);

    mainLoopIsReady = true;
}

void loop() {
  setBasicPositions();

  while (mainLoopIsReady) {
    
    mpu.update();
    
    if (mpuReady) {
      // X -> right / left       Y -> forward / backward
      targetRoll = constrain(mpu.getAngleX(), -35.0f, 35.0f);
      targetPitch = constrain(mpu.getAngleY(), -35.0f, 35.0f);
      
      // LOW pass filter (LPF)
      currentRoll += mpuAlpha * (targetRoll - currentRoll);
      currentPitch += mpuAlpha * (targetPitch - currentPitch);

      // AXIS crossing for IK
      body.orientation.pitch = currentRoll * mpuCompensationGain; 
      body.orientation.roll = currentPitch * mpuCompensationGain; 
    } else {
      // Robot isn`t standing -> block 0 deg
      body.orientation.pitch = 0.0f;
      body.orientation.roll = 0.0f;
    }
    // -----------------------------------------

    legSolve[LEGLF] = ikLegLF.solve();
    legSolve[LEGRF] = ikLegRF.solve();
    legSolve[LEGLH] = ikLegLH.solve();
    legSolve[LEGRH] = ikLegRH.solve();

    for (int8_t i = 0; i < LEGS_NUM; i++)
      if (legSolve[i].isSolved)
        setPosition(legs[i]);
  }
}

void serviceSetup() {
  serviceLoopIsReady = true;
}

void serviceLoop(void *parameter) {
  serviceSetup();

  // Waiting for conection and update
  while (1) {
    bool dataUpdated = BP32.update();
    if (dataUpdated) {
      standUp();
      
      // MPU calibration
#ifdef BAUD
      Serial.println(F("Wstaje... Czekam 1.5s na pozycje docelowa."));
#endif
      // wait for servos
      vTaskDelay(1500 / portTICK_PERIOD_MS); 
      
#ifdef BAUD
      Serial.println(F("Kalibruje idealny poziom. NIE RUSZAJ ROBOTA!"));
#endif
      mpu.calcOffsets(); // Save 0
      mpuReady = true;   // unlock robot balancing
#ifdef BAUD
      Serial.println(F("Samopoziomowanie wlaczone!"));
#endif

      break;
    }
  }

  // Read Controller & Walk generate
  while (1) {
    bool dataUpdatedFromController = BP32.update();

    if (dataUpdatedFromController) {
      processControllers();
    }



    static unsigned long lastTime = micros();
    unsigned long now = micros();
    float dt = (now - lastTime) / 1000000.0f;
    lastTime = now;

    gait.update(dt);
  }
}
