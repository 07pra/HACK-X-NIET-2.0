#include <LiquidCrystal.h>

#define TRIGGER_PIN_1 2
#define ECHO_PIN_1 3
#define TRIGGER_PIN_2 12
#define ECHO_PIN_2 13
#define RELAY_PIN_1 4
#define RELAY_PIN_2 11

LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // Pins for LCD (RS, E, D4, D5, D6, D7)

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  long duration, distance_1, distance_2;

  // First ultrasonic sensor
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);
  duration = pulseIn(ECHO_PIN_1, HIGH);
  distance_1 = duration * 0.034 / 2;

  // Second ultrasonic sensor
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);
  duration = pulseIn(ECHO_PIN_2, HIGH);
  distance_2 = duration * 0.034 / 2;

  // Check if both sensors detect an object within a certain range
  if (distance_1 < 30 && distance_2 < 30) {
    // Both sensors detect an object, initiate charging
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Charging Started");
  } else {
    // No object detected, stop charging
    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_2, LOW);
    lcd.setCursor(0, 0);
    lcd.print("No Vehicle Detected");
  }

  delay(500);
}