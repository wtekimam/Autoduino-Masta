/* AUTOMATIODUINO 0.1
    FOR 1 LIGHT (Pin 13)

    Functions include:
      1. Motion sensor (pin 2)
      2. Light sensor (SCL - Pin A5, SDA - Pin A4)
*/

// LIBRARIES FOR LIGHT SENSOR //
#include <Wire.h>
#include <BH1750.h>

////////// DEFINING PINS //////////
const unsigned int pirPin = 2; // Light sensor
const unsigned int lightPin = 13; // Output for light


// VARIABLES FOR MOTION SENSOR
int offTimer = 60;        // time in secs before sensor would have to be retriggered
int countdown = offTimer; // for countdown of timer
bool motionOn;            // for turning on sensor

// VARIABLES FOR LIGHT SENSOR
BH1750 lightMeter;
uint16_t lux;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(lightPin, OUTPUT);

  digitalWrite(lightPin, LOW);

  Serial.begin(9600);
  lightMeter.begin();
}

void loop() {
  checkLightMeter();
}

