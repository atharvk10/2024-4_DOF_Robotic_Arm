#include "Servos.h"
#include "Sensors.h"
#include "StepMotor.h"
#include <math.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQ 60

Adafruit_PWMServoDriver servoBoard = Adafruit_PWMServoDriver();

//Servo Ports
int forearmServo = 3;
int clawServo = 4;
int leftShoulderServo = 8; //Shoulder arm that has the forerarm servo attached.
int rightShoulderServo = 9;
int wristServo = 15;

//MIN and MAX PUlSE NUMBERS (with respect to the vertical axis from the base of the robot)
//The angles in degrees is in respect to the opening of the stepper motor plugin
    //0 degrees is at the opening, 180 is away from the opening

int clawOpen = 510; 
int clawClose = 90;

int wristMin = 80; //180 degrees
int wirstMiddle = 300; //90 degrees
int wristMax = 525; //0 degrees

int forearmMin = 80; //180 degrees
int forearmMiddle = 285; //90 degrees
int forearmMax = 510; //0 degrees

//Respect to the servo side of left servo shoulder
int leftShoulderMin = 85; //0 degrees
int leftShoulderMiddle = 295; //90 degrees
int leftShoulderMax = 510; //180 degrees

//Respect to the servo of right shoulder
int rightShoulderMin = 85;
int rightShoulderMiddle = 295;
int rightShoulderMax = 517;

//Variables to track current positions of the servos
int secDelay = 500;
int currentShoulderAngle; //with respect to the left servo shoulder
int currentForearmAngle; 

int currentWristAngle;
int currentClawAngle;

//Setting initial positions of the robotic arm
int startShoulderAngle = 60;
int startClawAngle;
int startForearmAngle = 135;

//Threads, having method checks in loops to make sure that the current method is done.

/*How does Servo PWM work?

    Most servos are controlled by PWM.
    By giving it a pulse width, it moves accordingly.
    The signals that we give the servos have a period of 20 ms, which is 50 hz

    A servo's position is determined by the width of the pulse.
        If we have a longer pulse/longer on time, then the servo will rotate more and longer
        If its a shorter pulse, then the servo will rotate less and for less time

    If I pass a larger PWM value in the method, I am telling the servo to move a far distance and much longer.
    When we find the pulse numbers for each servo, it's the numbers that describe how long the pulse has to be on for.

    A MIN pulse means it tells the servo to rotate to it's extreme position in NEAREST DIRECTION.
    A MAX pulse means it tells the servo to rotate to it's extreme position in the OPPOSITE DIRECTION

    for the setPWM() method --> first parameter is what servo we are controlling
        - Second parameter is essentially says WHEN should we make the pulse go from low to high (essentially turn on the signal)
        - Third parameter tells us WHEN we should make the pulse from go high to low (essentially turn off the signal)

        The pulse width length of one cycle is equal to third parameter - second parameter
        (THE LONGER THE WIDTH LENGTH IS, THE LONGER THE SERVO MOVES FOR)

        The second and third parameters are measured from 0 - 4096.


*/


void initServos() {
    servoBoard.begin();
    servoBoard.setPWMFreq(FREQ);

    delay(500);
    //Setting the initial positions of the robotic arm (only shoulder)
    servoBoard.setPWM(leftShoulderServo, 0, map(startShoulderAngle, 0, 180, leftShoulderMax, leftShoulderMin));
    servoBoard.setPWM(rightShoulderServo, 0, map(startShoulderAngle, 0, 180, rightShoulderMin, rightShoulderMax));
    delay(2000);
    servoBoard.setPWM(forearmServo, 0, forearmMin);
    delay(1000);
    servoBoard.setPWM(wristServo, 0, wristMin);   
    delay(500);
    //Set the initial variables for the initial angles

    currentShoulderAngle = startShoulderAngle;
    currentForearmAngle = 180;
    currentWristAngle = 180;

    moveClaw(0);
    delay(1000);
    moveClaw(135);
    delay(1500);


}

void perform()
{   
    delay(1000);
    boolean completedRun = false; //Determines if we finished placing an object or not
    int colorNum = readColor(); //Gets the color that we read from the sensor after detecting there is an object


    if(colorNum == 1 && !completedRun) { //If the object is red
        delay(200);
        printf("Moving to pick up the red object from the sensor.");
        pickUpObject();
        printf("Picked up the red object.");

        delay(500);
        printf("Placing the red object in the bin.");
        rotate(100, 60); //Moves to the right by 45 degrees at a speed of 60 RPM
        dropObject();
        printf("Placed the red object in the bin");

        completedRun = true;
        delay(2000);
        return;

    } else if(colorNum == 2 && !completedRun) { //If the object is green
        delay(200);
        printf("Moving to pick up the green object from the sensor.");
        pickUpObject();
        printf("Picked up the green object");

        delay(500);
        printf("Placing the green object in the bin.");
        dropObject();
        printf("Placed the green object in the bin.");

        completedRun = true;
        delay(2000);
        return;


    }  else if(colorNum == 3 && !completedRun) {// If the object is blue 
        delay(200);
        printf("Moving to pick up the blue object from the sensor.");
        pickUpObject();
        printf("Picked up the blue object");

        delay(500);
        printf("Placing the blue object in the bin.");
        rotate(-100, 60);
        dropObject();
        printf("Placed the blue object in the bin.");

        completedRun = true;
        delay(2000);
        return;

    } else {
        delay(1000);
        printf("No object can be placed");
    }

}

void moveShoulder(int angle)
{   
     int leftSignal;
     int rightSignal;

     if(angle > currentShoulderAngle) {
         for(int i = currentShoulderAngle; i <= angle; i += 5) {
            leftSignal = map(i, 0, 180, leftShoulderMax, leftShoulderMin);
            rightSignal = map(i, 0, 180, rightShoulderMin, rightShoulderMax);
            delay(10);
            servoBoard.setPWM(leftShoulderServo, 0, leftSignal);
            delay(10);
            servoBoard.setPWM(rightShoulderServo, 0, rightSignal);
         }

     } else {
        for(int i = currentShoulderAngle; i >= angle; i -= 5) {
            leftSignal = map(i, 0, 180, leftShoulderMax, leftShoulderMin);
            rightSignal = map(i, 0, 180, rightShoulderMin, rightShoulderMax);
            delay(10);
            servoBoard.setPWM(leftShoulderServo, 0, leftSignal);
            delay(10);
            servoBoard.setPWM(rightShoulderServo, 0, rightSignal);
        }

     }

    servoBoard.setPWM(leftShoulderServo, 0, leftSignal);
    servoBoard.setPWM(rightShoulderServo, 0, rightSignal);

    currentShoulderAngle = angle;
    

}

void moveForearm(int angle)
{

    int forearmSignal;
    if(angle > currentForearmAngle) {
        for(int i = currentForearmAngle; i <= angle; i += 5) {
            forearmSignal = map(i, 0, 180, forearmMax, forearmMin);
            servoBoard.setPWM(forearmServo, 0, forearmSignal);
            delay(10);
         }

     } else {
        for(int i = currentForearmAngle; i >= angle; i -= 5) {
            forearmSignal = map(i, 0, 180, forearmMax, forearmMin);
            servoBoard.setPWM(forearmServo, 0, forearmSignal);
            delay(10);
         }

     }
    
    servoBoard.setPWM(forearmServo, 0, map(angle, 0, 180, forearmMax, forearmMin));

    currentForearmAngle = angle;
    
}

void moveClaw(int angle) {

    int clawSignal = map(angle, 0, 180, clawClose, clawOpen);
    servoBoard.setPWM(clawServo, 0, clawSignal);
    currentClawAngle = angle;
    delay(500);
}

void moveWrist(int angle) 
{
    int wristSignal;
    if(angle > currentWristAngle) {
        for(int i = currentWristAngle; i <= angle; i += 5) {
            wristSignal = map(i, 0, 180, wristMin, wristMax);
            servoBoard.setPWM(wristServo, 0, wristSignal);
            delayMicroseconds(10);        
        }

    } else {
        for(int i = currentWristAngle; i >= angle; i -= 5) {
            wristSignal = map(i, 0, 180, wristMin, wristMax);
            servoBoard.setPWM(wristServo, 0, wristSignal);
            delayMicroseconds(10);
        }
    }


    servoBoard.setPWM(wristServo, 0, map(angle, 180, 0, wristMin, wristMax));
    currentWristAngle = angle;

}

void moveTo(double x, double y, double angleInDegrees)
{   
    //Everything is radians with cos and sin! We need to convert the final answers for angles into degrees
    //Lengths are measured from starting to next servo horn
    double shoulderLength = 18;
    double forearmLength = 17;
    double wristLength = 18;

    if(shoulderLength + forearmLength + wristLength < (x + y) || x == 0 || y == 0 || angleInDegrees < 0 || angleInDegrees > 180) {
        Serial.println("x, y position, or angle is not valid.");
        return;
    }

    

    double angleInRadians = angleInDegrees * (PI/ 180);
    double shoulderAngleOne, shoulderAngleTwo;
    double forearmAngleOne, forearmAngleTwo;
    double wristAngleOne, wristAngleTwo; 

    double shoulderNum = 34 + pow(x, 2) + pow(y, 2);
    double shoulderDenom = 35 * sqrt(pow(x, 2) + pow(y, 2));
    shoulderAngleOne = atan(y/x) + acos(shoulderNum / shoulderDenom);
    shoulderAngleTwo = atan(y/x) - acos(shoulderNum / shoulderDenom);

    double forearmNumOne = y - 17.5 * sin(shoulderAngleOne);
    double forearmDenomOne = x - 17.5 * cos(shoulderAngleOne);
    forearmAngleOne = atan(forearmNumOne / forearmDenomOne) - shoulderAngleOne;

    double forearmNumTwo = y - 17.5 * sin(shoulderAngleTwo);
    double forearmDenomTwo = x - 17.5 * cos(shoulderAngleTwo);
    forearmAngleTwo = atan(forearmNumTwo / forearmDenomTwo) - shoulderAngleTwo;

    wristAngleOne = angleInRadians - forearmAngleOne - shoulderAngleOne;
    wristAngleTwo = angleInRadians - forearmAngleTwo - shoulderAngleTwo;

    shoulderAngleOne = (shoulderAngleOne * 180)/PI;
    shoulderAngleTwo = (shoulderAngleTwo * 180)/PI;

    forearmAngleOne = (forearmAngleOne * 180)/PI;
    forearmAngleTwo = (forearmAngleTwo * 180)/PI;

    wristAngleOne = (wristAngleOne * 180)/PI;
    wristAngleTwo = (wristAngleTwo * 180)/PI;

    Serial.println(shoulderAngleOne);
    Serial.println(forearmAngleOne);
    Serial.println(wristAngleOne);

    if(shoulderAngleOne < 0) shoulderAngleOne += 180;
    if(forearmAngleOne < 0) forearmAngleOne += 180;
    if(wristAngleOne < 0) wristAngleOne += 180;

    Serial.println(shoulderAngleOne);
    Serial.println(forearmAngleOne);
    Serial.println(wristAngleOne);

    moveWrist(wristAngleOne);
    delay(3000);
    moveForearm(forearmAngleOne);
    delay(3000);
    moveShoulder(shoulderAngleOne);
    delay(3000);

     
}

void pickUpObject() {
    //Should follow the same movement and procedures for grabbing an object from the ramp
    //Should call the moveTo function here to pick up the objects accorindgly
}

void dropObject() {
    //Shoud follow the same movement and procedure for dropping an object in the basket.
    //The only difference is where the base rotates to place the object.
    //Should call the moveTo function here to pick up the objects accorindgly
}