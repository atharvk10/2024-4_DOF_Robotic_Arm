#include "StepMotor.h"

#define NUMOFSTEPS 800 
#define MAXMOTORSPEED 500 

#define HALFREV 400
#define FULLREV 800
#define SIDEREV 200

#define MOTORSPEED 150


int DIR = 7;
int STEP = 8;

Stepper baseMotor = Stepper(NUMOFSTEPS, STEP, DIR);
int motorDelay = 500;


void rotateNinety(int dir, int speed)
{
    baseMotor.setSpeed(speed);
    //1 is for clockwise, 0 is for counterclockwise
    if(dir == 1) baseMotor.step(SIDEREV);
    if(dir == 0) baseMotor.step(-SIDEREV);

    delay(motorDelay);
}

void rotateOneEighty(int speed)
{
    baseMotor.setSpeed(speed);
    delay(500);
   // digitalWrite(DIR, HIGH);
    baseMotor.step(HALFREV);
    delay(motorDelay);

}

void rotate(int numOfSteps, int dir, int speed) {
    
    baseMotor.setSpeed(speed);
    delay(500);
    if(dir == 1) baseMotor.step(numOfSteps);
    else baseMotor.step(-numOfSteps);
    
}

