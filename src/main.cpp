#include <Arduino.h>
#include "Sensors.h"
#include "Servos.h"
#include "StepMotor.h"

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    initSensors();
    delay(1000);
    initServos();
    delay(1000);
    moveForearm(125);
    delay(2000);
    

}

void loop() {
  moveTo(10, 5, 90);
  
  // boolean finishedRun = false;
  // while(!finishedRun) {
  //   placeObject();
  //   delay(500);

  //   finishedRun = true;
  // }




  





 
  
  

  
}

