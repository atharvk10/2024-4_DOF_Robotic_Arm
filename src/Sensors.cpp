#include "Sensors.h"

#define S0 37
#define S1 39
#define S2 41
#define S3 49
#define OUT 45

#define TRIGGER 31
#define ECHO 33

int redMin = 77, redMax = 126;
int greenMin = 72, greenMax = 122;
int blueMin = 74, blueMax = 117;

int redThreshold = 225;
int greenThreshold = 225;
int blueThreshold = 225;
double minDistance = 1.5;

/*
    How the TCS3200 sensor works? 
        - 8x8 array of photodioides
        - S2 and S3 select which color we want to detect
        - S0 and S1 which scales the output frequency (helps for optimization)

    How the HC-SRO4
        - Shoots ultrasonic sound.
        - Reads the time that it takes to reach back to the sensor.
            - Need to divide by 2 to account for just one distance travel.

*/

void initSensors() {

    //Initializing the color sensor
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);

    //Setting frequnecy scaling to 20%.
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    Serial.begin(9600);

    //Initializing the distance sensor
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}

bool checkIfVisible()
{   
    //Sends a pulse from the distance sensor.
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);

    //Calculates the distance
    long duration = pulseIn(ECHO, HIGH);
    long distance = (duration * 0.034)/2;
    
    Serial.println(distance);

    if(distance <= minDistance) {
        return true;
    } else {
        return false;
    }
}

int readColor()
{
    if(checkIfVisible) {
        //Checking for red
        digitalWrite(S2, LOW);
        digitalWrite(S3, LOW);
        int redFreq = pulseIn(OUT, LOW);
        if(redFreq > redMax) redFreq = redMax;
        if (redFreq < redMin) redFreq = redMin;
        int red = map(redFreq, redMin, redMax, 255, 0);
        
        delay(100);

        //Checking for blue 
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        int blueFreq = pulseIn(OUT, LOW);
        if(blueFreq > blueMax) blueFreq = blueMax;
        if(blueFreq < blueMin) blueFreq = blueMin;
        int blue = map(blueFreq, blueMin, blueMax, 255, 0);

        delay(100);

        //Checking for green
        digitalWrite(S2, HIGH);
        digitalWrite(S3, HIGH);
        int greenFreq = pulseIn(OUT, LOW);
        if(greenFreq > greenMax) greenFreq = greenMax;
        if(greenFreq < greenMin) greenFreq = greenMin;
        int green = map(greenFreq, greenMin, greenMax, 255, 0); 

        delay(100);

        // Serial.print(red);
        // Serial.print("       ");
        // Serial.print(green);
        // Serial.print("       ");
        // Serial.print(blue); 

        if(red > redThreshold && blue < blueThreshold && green < greenThreshold) {
            Serial.println("RED DETECTED");
            return 1;
        }

        if(green > greenThreshold && red < redThreshold && blue < blueThreshold) {
            Serial.println("GREEN DETECTED");
            return 2;
        }

        if(blue > blueThreshold && red > redThreshold && green > greenThreshold) {
            Serial.println("YELLOW DETECTED");
            return 3;
        }
        
    } else {
        Serial.print("Object not detected.");
    }
        //Checking for red
        
    Serial.println();
    return 0;
 
}  



