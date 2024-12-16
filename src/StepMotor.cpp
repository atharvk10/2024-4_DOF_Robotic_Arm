#include "StepMotor.h"

#define NUMOFSTEPS 800 
#define MAXMOTORSPEED 500 

#define HALFREV 400 //180 degrees
#define FULLREV 800 //360 degrees
#define SIDEREV 200 //90 degrees

#define MOTORSPEED 150

#define MS1 34
#define MS2 36
#define MS3 38

int DIR = 30;
int STEP = 28;

Stepper baseMotor = Stepper(NUMOFSTEPS, STEP, DIR);
int motorDelay = 1000;

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

void rotate(int steps, int speed) {
    baseMotor.setSpeed(speed);
    delay(500);
    baseMotor.step(steps);
    delay(motorDelay);
}

