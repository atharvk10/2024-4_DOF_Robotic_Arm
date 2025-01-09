#include "StepMotor.h"

#define NUMOFSTEPS 800 
#define MAXMOTORSPEED 500 

#define HALFREV 400
#define FULLREV 800
#define SIDEREV 200

#define MOTORSPEED 150
#define DIR 51
#define STEP 53

#define MS1 48
#define MS2 52
#define MS3 50


Stepper baseMotor = Stepper(NUMOFSTEPS, STEP, DIR);
int motorDelay = 500;

void initStepper() {

    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
}


void rotateNinety(int dir, int speed)
{
    // baseMotor.setSpeed(speed);
    // //1 is for clockwise, 0 is for counterclockwise
    // if(dir == 1) baseMotor.step(SIDEREV);
    // if(dir == 0) baseMotor.step(-SIDEREV);

    // delay(motorDelay);

    digitalWrite(DIR, HIGH);

    for(int i = 0; i < 100; i++) {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(1000);
        digitalWrite(STEP, LOW);
        delayMicroseconds(1000);
    }

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

