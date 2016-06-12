
/*
* ISP FINAL CODE
* June 2, 2016.
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Servo.h>
#include <math.h>

Servo ARM_SERVO;

//LED declaration
const int RED_LIGHT_1 = 13,
          YELLOW_LIGHT_1 = 12,
          GREEN_LIGHT_1 = 11;

const int RED_LIGHT_2 = 10,
          YELLOW_LIGHT_2 = 9,
          GREEN_LIGHT_2 = 8;

const int PEDESTRIAN_LIGHT_RED = 7,
          PEDESTRIAN_LIGHT_GREEN = 2,
          STREET_LIGHT = 4,
          BUTTON_OUTPUT = 3;

const int BUTTON = A1,
          LDR_PIN = A0;


const int IR_SENSOR = A2;

int ldrValue;

unsigned long currentTime, timeTurned;

bool armTurned = 0;

long multiplier = 1;

long double loopTimer = 0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int getRED_LIGHT_2 () {
    return digitalRead(RED_LIGHT_2);
}

int getBUTTON () {
    return digitalRead(BUTTON);
}

int getIR() {
    return analogRead(IR_SENSOR);
}

int getLDR() {
    return analogRead(LDR_PIN);
}

int getArm (){
    return ARM_SERVO.read();
}
void on(int LED) {
    digitalWrite (LED, HIGH);
}

void off(int LED) {
    digitalWrite(LED, LOW);
}

void turnArm(bool direction) {
  while (getArm() != 90 * direction)
    ARM_SERVO.write(getArm()+(direction)?1:-1);
}

void switchGreen(int red, int green) {
    off(red);
    on(green);
}

void switchYellow(int green, int yellow) {
    off(green);
    on(yellow);
}

void switchRed(int yellow, int red) {
    off(yellow);
    on(red);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
*  This method initializes all compoenents of the circuit.
*/
void setup() {
    pinMode (RED_LIGHT_1, OUTPUT);
    pinMode (YELLOW_LIGHT_1, OUTPUT);
    pinMode (GREEN_LIGHT_1, OUTPUT);

    pinMode (RED_LIGHT_2, OUTPUT);
    pinMode (YELLOW_LIGHT_2, OUTPUT);
    pinMode (GREEN_LIGHT_2, OUTPUT);

    pinMode (PEDESTRIAN_LIGHT_RED, OUTPUT);
    pinMode (PEDESTRIAN_LIGHT_GREEN, OUTPUT);

    pinMode (STREET_LIGHT, OUTPUT);


    pinMode(LDR_PIN, INPUT);

    pinMode (BUTTON, INPUT);
    pinMode (BUTTON_OUTPUT, OUTPUT);
    digitalWrite (BUTTON_OUTPUT, HIGH);

    pinMode(IR_SENSOR, INPUT);

    ARM_SERVO.attach(6);
    ARM_SERVO.write(0);
    Serial.begin (9600);
}

/*
*  This method is the active loop of the system.
*/
void loop () {
    currentTime = millis();
    ldrValue = getLDR();



    Serial.println(getArm());

    //Turns on the street light
    if(ldrValue < 70) {
        on(STREET_LIGHT);
    } else {
        off(STREET_LIGHT);
    }

    //Increments seconds and counter
    if (currentTime >= 20 * multiplier) {
        loopTimer++;
        multiplier++;
    } 
    if (getArm() == 0 && getIR() < 2 ){
      turnArm(true);
      timeTurned = currentTime;
    }
    else if (getIR() >= 2 && currentTime - timeTurned >= 3000){
      turnArm(false);
    }
    
    if(loopTimer  > 600) {
        loopTimer = 0;
    }
    if (getBUTTON() == HIGH && getRED_LIGHT_2() == HIGH) {
        loopTimer += (300-loopTimer)/250;
    }

    if (loopTimer >= 0 && loopTimer < 300) {

        if (loopTimer < 250) {
            switchGreen(RED_LIGHT_1, GREEN_LIGHT_1);
            off(PEDESTRIAN_LIGHT_GREEN);
            on(PEDESTRIAN_LIGHT_RED);
        }
        if(loopTimer >= 250) {
            switchYellow(GREEN_LIGHT_1, YELLOW_LIGHT_1);
        }

        switchRed(YELLOW_LIGHT_2, RED_LIGHT_2);

    }
    if(loopTimer >= 300 && loopTimer < 600) {

        if (loopTimer < 550) {
            switchGreen (RED_LIGHT_2, GREEN_LIGHT_2);

        }
        if(loopTimer < 450) {
            off(PEDESTRIAN_LIGHT_RED);
            on(PEDESTRIAN_LIGHT_GREEN);
        }
        if(loopTimer >= 550) {
            switchYellow(GREEN_LIGHT_2, YELLOW_LIGHT_2);
        }

        switchRed(YELLOW_LIGHT_1, RED_LIGHT_1);

    }
    if (loopTimer >=450 && loopTimer <600) {
        off(PEDESTRIAN_LIGHT_GREEN);
        if ((int)loopTimer%10 == 0) {
            on(PEDESTRIAN_LIGHT_RED);
        } else {
            off(PEDESTRIAN_LIGHT_RED);
        }
    }
}

