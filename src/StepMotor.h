#ifndef StepMotor_h
#define StepMotor_h

#include <Stepper.h>
#include <Arduino.h>

// Rotates the motor ninenty degrees
/*Paraneters:
    Dir - Specifies the direction we want to go (LEFT OR RIGHT)
    Speed - Sets the speed that the base rotates 90 degrees.
*/
void rotateNinety(int dir, int speed);

//Rotates the motor 180 degrees
/*Paraneters:
    Speed - Sets the speed that the base rotates 180 degrees.
*/
void rotateOneEighty(int speed);

//Rotates a number of steps at a certain speed
/*Paraneters:
    Steps - Number of steps that the motor moves
    Speed - Sets the speed that the base rotates
*/
void rotate(int steps, int speed);

#endif