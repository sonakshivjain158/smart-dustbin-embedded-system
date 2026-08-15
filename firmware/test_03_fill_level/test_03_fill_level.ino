// TEST 3
// Bin Fill-Level Detection

const int FILL_TRIG = 9;
const int FILL_ECHO = 8;

// Distance when bin is considered empty
const float EMPTY_DISTANCE = 30.0;

// Distance when bin is considered full
const float FULL_DISTANCE = 5.0;

float getFillDistance()
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

    Serial.println("Smart Dustbin - Fill Level Test");
    Serial.println("--------------------------------");
}

void loop()
{
    float distance = getFillDistance();

    int fillPercentage =
        calculateFillPercentage(distance);

    Serial.print("Garbage Distance: ");

    if (distance < 0)
    {
        Serial.println("Sensor Error");
    }
    else
    {
        Serial.print(distance);
        Serial.println(" cm");

        Serial.print("Bin Fill Level: ");
        Serial.print(fillPercentage);
        Serial.println("%");
    }

    Serial.println("--------------------------------");

    delay(1000);
}
