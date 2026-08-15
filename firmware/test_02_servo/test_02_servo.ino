#include <Servo.h>

// ---------- PIN DEFINITIONS ----------

const int TRIG_PIN = 7;
const int ECHO_PIN = 6;
const int SERVO_PIN = 5;

// ---------- SETTINGS ----------

const int DETECTION_DISTANCE = 20;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

Servo lidServo;

// ---------- SETUP ----------

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    lidServo.attach(SERVO_PIN);

    // Start with lid closed
    lidServo.write(CLOSED_ANGLE);

    Serial.println("SMART DUSTBIN");
    Serial.println("Automatic Lid Test");
    Serial.println("----------------------------");
}

// ---------- MEASURE DISTANCE ----------

float getDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);

    float distance = duration * 0.0343 / 2;

    return distance;
}

// ---------- MAIN LOOP ----------

void loop()
{
    float distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < DETECTION_DISTANCE)
    {
        Serial.println("Person detected!");
        Serial.println("Lid: OPEN");

        lidServo.write(OPEN_ANGLE);

        delay(3000);

        Serial.println("Lid: CLOSED");

        lidServo.write(CLOSED_ANGLE);
    }
    else
    {
        lidServo.write(CLOSED_ANGLE);

        Serial.println("No person detected.");
        Serial.println("Lid: CLOSED");
    }

    Serial.println("----------------------------");

    delay(500);
}
