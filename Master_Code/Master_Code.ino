/* AUTOMATIODUINO 0.3
    FOR 1 LIGHT (Pin 13)

    Functions include:
      1. Motion sensor (pin 2, 5v)
      2. Light sensor (SCL - Pin A5, SDA - Pin A4, 3.3v)
      3. Keypad (Pin 5-12, From right to left)
*/

// LIBRARIES//
#include <Wire.h>
#include <BH1750.h>
#include <Keypad.h>

////////// DEFINING PINS //////////
const unsigned int pirPin = 2; // Light sensor
const unsigned int lightPin = 13; // Output for light

/////////////////////////////////
/////////// VARIABLES ///////////
/////////////////////////////////
bool allSensorOn = true; // for turning all the sensors on and off

/////////////////////////////////
/////// FOR MOTION SENSOR ///////
/////////////////////////////////
int offTimer = 10;        // time in secs before sensor would have to be retriggered
int countdown = offTimer; // for countdown of timer
bool motionOn;            // for turning on sensor

////////////////////////////////
/////// FOR LIGHT SENSOR ///////
////////////////////////////////
BH1750 lightMeter;
uint16_t lux;

////////////////////////////////
////////// FOR KEYPAD //////////
////////////////////////////////
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char key;

// Connect the keypad to these Arduino pins.
byte rowPins[ROWS] = { 8, 7, 6, 5 };
byte colPins[COLS] = { 12, 11, 10, 9 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS );



////////////////////////////
////// MAIN FUNCTIONS //////
////////////////////////////
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(lightPin, OUTPUT);

  digitalWrite(lightPin, LOW);

  Serial.begin(9600);
  lightMeter.begin();
}

void loop() {
  readKeyInput();
  if (allSensorOn)
    checkLightMeter();
}

