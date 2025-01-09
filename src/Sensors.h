#ifndef Sensors_h
#define Sensors_h

#include "HCSR04.h"
#include "tcs3200.h"
#include <Arduino.h>

//Initializing the sensors for the robot
void initSensors();

//Checks if an object is close enough near the distance sensor (returns true or false)
bool checkIfVisible();

//Checks the color of the object near the sensor (will return 1, 2, or 3 depending on what color is read).
int readColor(); 

#endif