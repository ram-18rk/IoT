#include <Servo.h>

// Ultrasonic Sensor Pins
const int trigPin = 2;
const int echoPin = 9;

// LED Pins
const int redLED = 6;
const int greenLED = 7;

// Servo Objects
Servo radarServo; // Radar scanning servo
Servo gunServo;   // Gun tracking servo

// Variables
long duration;
int distance;
const int gunServoPin = 11;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.begin(9600);

  radarServo.attach(12);        // Radar scanning
  gunServo.attach(gunServoPin); // Gun tracking
  gunServo.write(90);           // Start at center
}

void loop() {
  // Sweep left to right
  for (int angle = 15; angle <= 165; angle++) {
    scanAndReact(angle);
  }

  // Sweep right to left
  for (int angle = 165; angle >= 15; angle--) {
    scanAndReact(angle);
  }
}

// Function to scan and react to distance
void scanAndReact(int angle) {
  radarServo.write(angle);
  delay(30);
  distance = calculateDistance();

  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");

  if (distance < 10) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    gunServo.write(angle); // Aim gun
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    gunServo.write(90);    // Reset gun to center
  }
}

// Function to calculate distance
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}