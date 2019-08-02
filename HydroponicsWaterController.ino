

#include "MeasureResult.h"

#define SENSE_WATER_MIN_THRESHOLD 100
#define MEASURE_DRIVER_PIN 9
#define WATER_LOW_PIN A0
#define WATER_HIGH_PIN A1

#define PUMP_PIN1 11
#define PUMP_PIN2 10

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PUMP_PIN1, OUTPUT);
  pinMode(PUMP_PIN2, OUTPUT);
  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(PUMP_PIN2, LOW);


  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

MeasureResult measureWaterLevel() {
  pinMode(MEASURE_DRIVER_PIN, OUTPUT);
  digitalWrite(MEASURE_DRIVER_PIN, HIGH);
  delayMicroseconds(100); // Allow caps to charge

  MeasureResult result;
  result.tankIsFull = analogRead(WATER_HIGH_PIN) > SENSE_WATER_MIN_THRESHOLD;
  result.tankIsEmpty = analogRead(WATER_LOW_PIN) <= SENSE_WATER_MIN_THRESHOLD;

  digitalWrite(MEASURE_DRIVER_PIN, LOW);
  pinMode(MEASURE_DRIVER_PIN, INPUT);

  return result;
}

void enablePump() {
  digitalWrite(PUMP_PIN1, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}


void disablePump() {
  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  delay(500);
  MeasureResult waterLevel = measureWaterLevel();
  if (waterLevel.tankIsFull) {
    enablePump();
  } else if (waterLevel.tankIsEmpty) {
    disablePump();
  }
}
