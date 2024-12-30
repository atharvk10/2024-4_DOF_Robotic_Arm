#include <Arduino.h>
#include "Sensors.h"
#include "Servos.h"
#include "StepMotor.h"

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    initSensors();
    initServos();

    moveClaw(180);

}

void loop() {
  // boolean finishedRun = false;
  // while(!finishedRun) {
  //   placeObject();
  //   delay(500);

  //   finishedRun = true;
  // }

  delay(1000);
  moveClaw(180);
  delay(1000);
  moveClaw(90);
  delay(1000);
  moveClaw(0);
  



      

















  





 
  
  

  
}

