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
    delay(2000);
    moveShoulder(65);
    moveForearm(125);
    moveWrist(90);





}

void loop() {
  // boolean finishedRun = false;
  // while(!finishedRun) {
  //   placeObject();
  //   delay(500);

  //   finishedRun = true;
  // }





      

















  





 
  
  

  
}

