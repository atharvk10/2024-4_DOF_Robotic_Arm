#include "Servos.h"
#include "Sensors.h"
#include "StepMotor.h"
#include <math.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQ 50

Adafruit_PWMServoDriver servoBoard = Adafruit_PWMServoDriver();

//Servo Ports
int clawServo = 4;
int leftShoulderServo = 0; //Shoulder arm that has the forerarm servo attached (looking at it from the front ahead).
int rightShoulderServo = 3;
int forearmServo = 7;
int wristServo = 11;


//MIN and MAX PUlSE NUMBERS (with respect to the vertical axis from the base of the robot)
//The angles in degrees is in respect to the opening of the stepper motor plugin
    //0 degrees is at the opening, 180 is away from the opening

int clawOpen = 525; 
int clawHalfOpen = 313;
int clawClose = 100;

int wristMax = 515; //180 degrees
int wirstMiddle = 300; //90 degrees
int wristMin = 85; //0 degrees

int forearmMax = 525; //180 degrees
int forearmMiddle = 315; //90 degrees
int forearmMin = 110; //0 degrees

//Respect to the servo side of left servo shoulder (DONE)
int leftShoulderMin = 85; //0 degrees
int leftShoulderMiddle = 313; //90 degrees
int leftShoulderMax = 540; //180 degrees

//Respect to the servo of right shoulder
int rightShoulderMin = 550; //0 degrees
int rightShoulderMiddle = 325; //90 degrees
int rightShoulderMax = 110; //180 degrees

//Variables to track current positions of the servos
int secDelay = 500;
int currentShoulderAngle; //with respect to the left servo shoulder
int currentForearmAngle; 

int currentWristAngle;
int currentClawAngle;

//Setting initial positions of the robotic arm
int startShoulderAngle = 90;
int startForearmAngle = 90;
int startWristAngle = 135;
int startClawAngle;


void initServos() {
    servoBoard.begin();
    servoBoard.setPWMFreq(FREQ);

    //Setting the initial positions of the robotic arm (only shoulder)
    servoBoard.setPWM(leftShoulderServo, 0, map(startShoulderAngle, 0, 180, leftShoulderMin, leftShoulderMax));
    servoBoard.setPWM(rightShoulderServo, 0, map(startShoulderAngle, 0, 180, rightShoulderMin, rightShoulderMax));
    delay(2000);
    servoBoard.setPWM(forearmServo, 0, map(startForearmAngle, 0, 180, forearmMin, forearmMax));
    delay(1000);
    servoBoard.setPWM(wristServo, 0, map(startWristAngle, 0, 180, wristMin, wristMax));   
    delay(2000);

    //Set the initial variables for the initial angles
    currentShoulderAngle = startShoulderAngle;
    currentForearmAngle = startForearmAngle;
    currentWristAngle = startWristAngle;
    // moveClaw(0);
    // delay(1000);
    // moveClaw(135);
    // delay(1500);


}

void placeObject()
{   
    delay(1000);
    boolean completedRun = false;
    int colorNum = checkColor();
    if(colorNum == 1 && !completedRun) { //If the object is red
        delay(200);
        goHome();
        moveTo(50, 60, 70);
        printf("Moving to pick up the red object from the sensor.");
        grabObject();
        printf("Picked up the red object.");

        delay(500);
        printf("Placing the red object in the bin.");
        rotateOneEighty(100);
        moveTo(50, 60, 70);
        dropObject();
        printf("Placed the red object in the bin");

        completedRun = true;
        delay(2000);
        return;

    } else if(colorNum == 2 && !completedRun) { //If the object is green
        delay(200);
        goHome();
        delay(1000);
        moveTo(50, 60, 70);
        printf("Moving to pick up the green object from the sensor.");
        grabObject();
        printf("Picked up the green object");

        delay(500);
        printf("Placing the green object in the bin.");
        rotateNinety(0, 100);
        moveTo(50, 60, 70);
        dropObject();
        printf("Placed the green object in the bin.");

        completedRun = true;
        delay(2000);
        return;


    }  else if(colorNum == 3 && !completedRun) {// If the ob ject is blue 
        delay(200);
        goHome();
        delay(1000);
        printf("Moving to pick up the blue object from the sensor.");
        grabObject();
        printf("Picked up the blue object");

        delay(500);
        printf("Placing the blue object in the bin.");
        rotateNinety(1, 100);
        moveTo(50, 60, 70);
        dropObject();
        printf("Placed the blue object in the bin.");

        completedRun = true;
        delay(2000);
        return;

    } else {
        delay(1000);
        goHome();
        printf("No object can be placed");
    }


}

void moveShoulder(int angle)
{   
      if(angle < 0 || angle > 180) return;

     int finalLeftPWM = map(angle, 0, 180, leftShoulderMin, leftShoulderMax);
     int finalRightPWM = map(angle, 0, 180, rightShoulderMin, rightShoulderMax);

     int currentLeftPWM = map(currentShoulderAngle, 0, 180, leftShoulderMin, leftShoulderMax);
     int currentRightPWM = map(currentShoulderAngle, 0, 180, rightShoulderMin, rightShoulderMax);

    int leftStepDirection = (currentLeftPWM < finalLeftPWM) ? 5:-5;
    int rightStepDirection = (currentRightPWM < finalRightPWM) ? 5:-5;


    int rightPWM = currentRightPWM;
    if(currentLeftPWM > finalLeftPWM && currentRightPWM < finalRightPWM) {
        for(int leftPWM = currentLeftPWM; leftPWM > finalLeftPWM; leftPWM += leftStepDirection) {
            servoBoard.setPWM(leftShoulderServo, 0, leftPWM);
            servoBoard.setPWM(rightShoulderServo, 0, rightPWM);
            rightPWM += rightStepDirection;
            delay(25);

        }
    } else {
        for(int leftPWM = currentLeftPWM; leftPWM < finalLeftPWM; leftPWM += leftStepDirection) {
            servoBoard.setPWM(leftShoulderServo, 0, leftPWM);
            servoBoard.setPWM(rightShoulderServo, 0, rightPWM);
            rightPWM += rightStepDirection;
            delay(25);

        }
    }

    servoBoard.setPWM(leftShoulderServo, 0, finalLeftPWM);
    servoBoard.setPWM(rightShoulderServo, 0, finalRightPWM);

    currentShoulderAngle = angle;
    Serial.print("Shoulder moved to: ");
    Serial.print(angle);

}

void moveForearm(int angle)
{
    if(angle < 0 || angle > 180) return;

    int currentPWMValue = map(currentForearmAngle, 0, 180, forearmMin, forearmMax);
    int finalPWMValue = map(angle, 0, 180, forearmMin, forearmMax);
    
    int stepDirection = (currentPWMValue < finalPWMValue) ? 5:-5;

    if(currentPWMValue > finalPWMValue) {
        for(int pwm = currentPWMValue; pwm > finalPWMValue; pwm += stepDirection) {
            servoBoard.setPWM(forearmServo, 0, pwm);
            delay(20);
        }
    } else {
        for(int pwm = currentPWMValue; pwm < finalPWMValue; pwm += stepDirection) {
            servoBoard.setPWM(forearmServo, 0, pwm);
            delay(20);
        }
    }

    servoBoard.setPWM(forearmServo, 0, finalPWMValue);
    currentForearmAngle = angle;

    Serial.println("Forearm moved to: ");
    Serial.print(angle);
    
}

void moveWrist(int angle) 
{

    if(angle < 0 || angle > 180) return;

    int currentPWMValue = map(currentWristAngle, 0, 180, wristMin, wristMax);
    int finalPWMValue = map(angle, 0, 180, wristMin, wristMax);

    int stepDirection = (currentPWMValue < finalPWMValue) ? 5:-5;

    if(currentPWMValue > finalPWMValue) {
        for(int pwm = currentPWMValue; pwm > finalPWMValue; pwm += stepDirection) {
            servoBoard.setPWM(wristServo, 0, pwm);
            delay(20);
        }
    } else {
        for(int pwm = currentPWMValue; pwm < finalPWMValue; pwm += stepDirection) {
            servoBoard.setPWM(wristServo, 0, pwm);
            delay(10);
        }
    }

    servoBoard.setPWM(wristServo, 0, finalPWMValue);
    currentWristAngle = angle;

    Serial.println("Wrist moved to: ");
    Serial.print(angle);

}

void moveClaw(int angle) {

    if(angle < 0 || angle > 180) return;

    int clawSignal = map(angle, 0, 180, clawClose, clawOpen);
    servoBoard.setPWM(clawServo, 0, clawSignal);
    delay(500);
}

void moveTo(double Xe, double Ye, double AngleEInDeg)
{   
    double shoulderLength = 17.5; //Checked
    double forearmLength = 17; //Checked
    double l3 = 10; //Not checked

    //Need to check if input makes sense
    if(Xe > shoulderLength + forearmLength + l3 || Ye > shoulderLength + forearmLength + l3 || AngleEInDeg > 180) return;

    double AngleEInRads = (AngleEInDeg * (M_PI))/180;

    //Position of the wrist in x y plane
    double Xw = Xe - l3 * cos(AngleEInRads);
    double Yw = Ye - l3 * sin(AngleEInRads);

    //Total length from base of the robot to final wrist position
    double wristDistance = sqrt(pow(Xw, 2) + pow(Yw, 2));

    //Calculating angles within the triangle (from law of cosines)
    double alpha = atan(Yw/Xw);
    double betaEquation = (pow(wristDistance, 2) - pow(shoulderLength, 2) - pow(forearmLength, 2)) / (-2 * shoulderLength * forearmLength);
    double beta = acos(betaEquation);
    double gammaEquation = (pow(forearmLength, 2) - pow(shoulderLength, 2) - pow(wristDistance, 2)) / (-2 * shoulderLength * wristDistance);
    double gamma = acos(gammaEquation);

    //Calculating the angles for the links and converting to degrees
    double shoulderAngle = (alpha - gamma) * (180/M_PI);
    double forearmAngle = (M_PI - beta) * (180/M_PI);
    double wristAngle = (AngleEInRads - shoulderAngle - forearmAngle) * (180/M_PI);

    //Adjusting the shoulder angle to be between the range of the servos
    shoulderAngle = fmod(shoulderAngle, 360);
    if(shoulderAngle < 0) shoulderAngle += 360;
    if(shoulderAngle > 180) shoulderAngle = 360 - shoulderAngle;

    //Adjusting the forearm angle to be between the range of the servos
    forearmAngle = fmod(forearmAngle, 360);
    if(forearmAngle < 0) forearmAngle += 360;
    if(forearmAngle > 180) forearmAngle = 360 - forearmAngle;

    wristAngle = fmod(wristAngle, 360);
    if(wristAngle < 0) wristAngle += 360;
    if(wristAngle > 180) wristAngle = 360 - wristAngle;


    Serial.print("Shoulder Angle: ");
    Serial.println(shoulderAngle);
    Serial.print("Forearm Angle: ");
    Serial.println(forearmAngle);
    Serial.print("Wrist Angle: ");
    Serial.println(wristAngle);

    // moveShoulder(shoulderAngle);
    // delay(1500);
    // moveForearm(forearmAngle);
    // delay(1500);
    // moveWrist(wristAngle);

     
}

void goHome() 
{   
    
   moveWrist(125);
   delay(2000);
   moveForearm(90);
   delay(2000);
   moveShoulder(90);

}
