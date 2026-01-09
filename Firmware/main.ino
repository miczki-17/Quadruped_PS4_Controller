#include "headers/uc_config.h"
#include "headers/controller_config.h"

#include "libs/IK/leg.h"
#include "libs/IK/legs_config.h"
#include "libs/IK/geometry.h"
#include "libs/IK/IK.h"
#include "libs/IK/IK.cpp"

#include "libs/Gait/gait.h"
#include "libs/Gait/gait.cpp"




#if PWM_CONTROLLER == ESP32
#include <ESP32_ISR_Servo.h>
#endif




#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];





figure body = {
  {0, 0, 0},
  {0, 0, 0}
};


Gait gait(legs, body);


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


//ul controllerCurrentMillis;
//ul controllerLastMillis = 0;
//ul controllerElapsedMillis;


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

  while (1) {
    bool dataUpdated = BP32.update();
    if (dataUpdated) {
      standUp();
      break;
    }
  }

  while (1) {

    bool dataUpdatedFromController = BP32.update();
    if (dataUpdatedFromController) {
      processControllers();
    }

    gait.move();
    gait.setDirection(WAIT);

  }
}
