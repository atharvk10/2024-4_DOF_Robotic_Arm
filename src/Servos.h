#define Servos_h
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

//Intializes all of the servos
void initServos();

//Place the object in the correct box/spot given the color (back = blue, right = red, left = green).
//Note to self: Implement the rotateNinety and rotateOneEighty methods for this.
void placeObject();

//Moves the two shoulder servos at the same time to a certain position.
//Note to self: Servos on the base are placed in opposite directions.
void moveShoulder(int angle);

//Moves the forearm to a certain position.
void moveForearm(int angle);

//Moves the wrist to a certain position.
void moveWrist(int angle);

void moveClaw(int angle);

//Implements IK algorithm to move the end effector to a XYZ position in space.
void moveTo(double Xe, double Ye, double AngleEInDeg);

//The robot goes back to home position
void goHome();

void grabObject();

void dropObject();

