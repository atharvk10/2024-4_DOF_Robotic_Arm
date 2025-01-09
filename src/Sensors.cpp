#include "Sensors.h"

#define S0 37
#define S1 39
#define S2 41
#define S3 49
#define OUT 45

#define TRIGGER 31
#define ECHO 33

//Values are PWM based
int redMin = 73, redMax = 207;
int greenMin = 75, greenMax = 201;
int blueMin = 72, blueMax = 181;

int threshold = 120;

double minDistance = 3.5;

void initSensors() {

    //Initializing the color sensor
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    Serial.begin(9600);

    //Initializing the distance sensor
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}

bool checkIfVisible()
{
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);


    double duration = pulseIn(ECHO, HIGH);
    double distance = (duration * 0.034)/2;
    
    Serial.println(distance);

    if(distance < minDistance) {
        return true;
    } else {
        return false;
    }
    
    delayMicroseconds(200);
}


int readColor()
{   


    delayMicroseconds(500);

        //Checking for red
        digitalWrite(S2, LOW);
        digitalWrite(S3, LOW);
        int redFreq = pulseIn(OUT, LOW);

        //Checking for blue 
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        int blueFreq = pulseIn(OUT, LOW);

        //Checking for green
        digitalWrite(S2, HIGH);
        digitalWrite(S3, HIGH);
        int greenFreq = pulseIn(OUT, LOW);

        // Serial.print(red);
        // Serial.print("       ");
        // Serial.print(green);
        // Serial.print("       ");
        // Serial.print(blue); 

        if(redFreq < threshold) {
            return 1;
        } else if(greenFreq < threshold) {
            return 2;
        } else if(blueFreq < threshold) {
            return 3;
        }

        return 0;
}  



