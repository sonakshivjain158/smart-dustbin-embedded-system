// TEST 4
// Fill Level + LED + Buzzer

const int FILL_TRIG = 9;
const int FILL_ECHO = 8;

const int GREEN_LED = 2;
const int YELLOW_LED = 3;
const int RED_LED = 4;

const int BUZZER = 10;

const float EMPTY_DISTANCE = 30.0;
const float FULL_DISTANCE = 5.0;

const int NEAR_FULL = 70;
const int FULL_LEVEL = 90;

float getDistance()
{
    digitalWrite(FILL_TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(FILL_TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(FILL_TRIG, LOW);

    long duration = pulseIn(FILL_ECHO, HIGH);

    if (duration == 0)
        return -1;

    return duration * 0.0343 / 2;
}

int calculateFillPercentage(float distance)
{
    if (distance < 0)
        return -1;

    float percentage =
        ((EMPTY_DISTANCE - distance) /
         (EMPTY_DISTANCE - FULL_DISTANCE)) *
        100;

    if (percentage < 0)
        percentage = 0;

    if (percentage > 100)
        percentage = 100;

    return (int)percentage;
}

void setup()
{
    Serial.begin(9600);

    pinMode(FILL_TRIG, OUTPUT);
    pinMode(FILL_ECHO, INPUT);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    pinMode(BUZZER, OUTPUT);

    Serial.println("Smart Dustbin - Status Test");
}

void loop()
{
    float distance = getDistance();

    int fillPercentage =
        calculateFillPercentage(distance);

    if (fillPercentage < 0)
    {
        Serial.println("Sensor Error");
        delay(1000);
        return;
    }

    Serial.print("Fill Level: ");
    Serial.print(fillPercentage);
    Serial.println("%");

    // Turn everything OFF first
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);

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

    Serial.println("----------------");

    delay(1000);
}
