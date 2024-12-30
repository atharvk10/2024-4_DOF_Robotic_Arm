#ifndef StepMotor_h
#define StepMotor_h

#include <Stepper.h>
#include <Arduino.h>

// Rotates the motor ninenty degrees
// Parameter DIR - Specifies the direction we want to go (LEFT OR RIGHT)
void rotateNinety(int dir, int speed);

//Rotates the motor 180 degrees
void rotateOneEighty(int speed);





#endif