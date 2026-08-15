// Smart Dustbin - Test 1
// HC-SR04 Proximity Sensor Test

const int TRIG_PIN = 7;
const int ECHO_PIN = 6;

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.println("Smart Dustbin - Proximity Sensor Test");
    Serial.println("--------------------------------------");
}

void loop()
{
    // Make sure trigger starts LOW
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Send 10 microsecond ultrasonic pulse
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure echo time
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Convert time to distance
    float distance = duration * 0.0343 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500);
}
