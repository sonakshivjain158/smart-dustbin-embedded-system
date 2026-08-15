#include <Servo.h>

// =================================================
// SMART DUSTBIN
// Complete Integrated Version
// =================================================

// ---------------- PIN DEFINITIONS ----------------

// Status LEDs
const int GREEN_LED = 2;
const int YELLOW_LED = 3;
const int RED_LED = 4;

// Servo
const int SERVO_PIN = 5;

// Proximity sensor
const int PROX_ECHO = 6;
const int PROX_TRIG = 7;

// Fill-level sensor
const int FILL_ECHO = 8;
const int FILL_TRIG = 9;

// Buzzer
const int BUZZER = 10;

// ---------------- CONFIGURATION ----------------

const float DETECTION_DISTANCE = 20.0;

const float EMPTY_DISTANCE = 30.0;
const float FULL_DISTANCE = 5.0;

const int NEAR_FULL = 70;
const int FULL_LEVEL = 90;

const int LID_CLOSED = 0;
const int LID_OPEN = 90;

const unsigned long LID_OPEN_TIME = 3000;

// ---------------- SERVO ----------------

Servo lidServo;

// =================================================
// DISTANCE MEASUREMENT
// =================================================

float measureDistance(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration =
        pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
    {
        return -1;
    }

    float distance =
        duration * 0.0343 / 2;

    return distance;
}

// =================================================
// FILL LEVEL CALCULATION
// =================================================

int calculateFillPercentage(float distance)
{
    if (distance < 0)
    {
        return -1;
    }

    float percentage =
        ((EMPTY_DISTANCE - distance) /
         (EMPTY_DISTANCE - FULL_DISTANCE)) *
        100;

    if (percentage < 0)
    {
        percentage = 0;
    }

    if (percentage > 100)
    {
        percentage = 100;
    }

    return (int)percentage;
}

// =================================================
// STATUS INDICATORS
// =================================================

void updateStatus(int fillPercentage)
{
    // Turn LEDs and buzzer OFF
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);

    noTone(BUZZER);

    if (fillPercentage < 0)
    {
        return;
    }

    if (fillPercentage < NEAR_FULL)
    {
        digitalWrite(GREEN_LED, HIGH);

        Serial.println("STATUS: NORMAL");
    }

    else if (fillPercentage < FULL_LEVEL)
    {
        digitalWrite(YELLOW_LED, HIGH);

        Serial.println("STATUS: NEAR FULL");
    }

    else
    {
        digitalWrite(RED_LED, HIGH);

        tone(BUZZER, 1000);

        Serial.println("STATUS: FULL");
    }
}

// =================================================
// SETUP
// =================================================

void setup()
{
    Serial.begin(9600);

    // LEDs
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // Buzzer
    pinMode(BUZZER, OUTPUT);

    // Proximity sensor
    pinMode(PROX_TRIG, OUTPUT);
    pinMode(PROX_ECHO, INPUT);

    // Fill sensor
    pinMode(FILL_TRIG, OUTPUT);
    pinMode(FILL_ECHO, INPUT);

    // Servo
    lidServo.attach(SERVO_PIN);
    lidServo.write(LID_CLOSED);

    Serial.println("================================");
    Serial.println(" SMART DUSTBIN SYSTEM");
    Serial.println("================================");
}

// =================================================
// MAIN LOOP
// =================================================

void loop()
{
    // ---------------------------------------------
    // 1. Read proximity sensor
    // ---------------------------------------------

    float proximityDistance =
        measureDistance(PROX_TRIG, PROX_ECHO);

    // ---------------------------------------------
    // 2. Read fill-level sensor
    // ---------------------------------------------

    float fillDistance =
        measureDistance(FILL_TRIG, FILL_ECHO);

    // ---------------------------------------------
    // 3. Calculate fill percentage
    // ---------------------------------------------

    int fillPercentage =
        calculateFillPercentage(fillDistance);

    // ---------------------------------------------
    // 4. Display sensor information
    // ---------------------------------------------

    Serial.println();

    Serial.print("Proximity Distance: ");

    if (proximityDistance < 0)
        Serial.println("ERROR");
    else
    {
        Serial.print(proximityDistance);
        Serial.println(" cm");
    }

    Serial.print("Garbage Distance: ");

    if (fillDistance < 0)
        Serial.println("ERROR");
    else
    {
        Serial.print(fillDistance);
        Serial.println(" cm");
    }

    Serial.print("Fill Level: ");

    if (fillPercentage < 0)
        Serial.println("ERROR");
    else
    {
        Serial.print(fillPercentage);
        Serial.println("%");
    }

    // ---------------------------------------------
    // 5. Update status LEDs + buzzer
    // ---------------------------------------------

    updateStatus(fillPercentage);

    // ---------------------------------------------
    // 6. Automatic lid
    // ---------------------------------------------

    if (proximityDistance > 0 &&
        proximityDistance < DETECTION_DISTANCE)
    {
        Serial.println("PERSON DETECTED");
        Serial.println("LID: OPEN");

        lidServo.write(LID_OPEN);

        delay(LID_OPEN_TIME);

        lidServo.write(LID_CLOSED);

        Serial.println("LID: CLOSED");
    }
    else
    {
        lidServo.write(LID_CLOSED);
    }

    Serial.println("--------------------------------");

    delay(500);
}
