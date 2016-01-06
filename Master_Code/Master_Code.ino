/* AUTOMATIODUINO 0.3
    FOR 1 LIGHT (Pin 13)

    Functions include:
      1. Motion sensor (pin 4, 5v)
      2. Light sensor (SCL - Pin A5, SDA - Pin A4, 3.3v)
      3. Keypad (Pin 5-12, From right to left)
      4. Buttons (Pin 1-3)
*/

// LIBRARIES//
#include <Wire.h>
#include <BH1750.h>
#include <Keypad.h>

////////// DEFINING PINS //////////
const unsigned int pirPin = 4; // Light sensor
const unsigned int lightPin = 12; // Output for light
const unsigned int btnOn = 1;
const unsigned int btnOff = 2;
const unsigned int btnAuto = 3;

/////////////////////////////////
/////////// VARIABLES ///////////
/////////////////////////////////
bool allSensorOn = true; // for turning all the sensors on and off
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


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
byte colPins[COLS] = { 13, 11, 10, 9 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS );



////////////////////////////
////// MAIN FUNCTIONS //////
////////////////////////////
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(lightPin, OUTPUT);
  
  pinMode(btnOn, INPUT);
  pinMode(btnOff, INPUT);
  pinMode(btnAuto, INPUT);

  digitalWrite(lightPin, HIGH);

  Serial.begin(9600);
  lightMeter.begin();
}

void loop() {
  int on = digitalRead(btnOn);
  int off = digitalRead (btnOff);
  int automatic = digitalRead (btnAuto);

  // read the state of the switch into a local variable:
  int readingOn = digitalRead(btnOn);
  int readingOff = digitalRead(btnOff);
  int readingAuto = digitalRead(btnAuto);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingOn != buttonState || readingOff != buttonState || readingAuto != buttonState ) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (automatic == HIGH) {
      allSensorOn = true;
      Serial.println("Auto");
      readKeyInput();
      if (allSensorOn)
        checkLightMeter();
    }
    else if (off == HIGH)
    {
      Serial.println("Off");
      digitalWrite(lightPin, LOW);
      allSensorOn = false;
    }
    else if (on == HIGH) {
      Serial.println("On");
      digitalWrite(lightPin, HIGH);
      allSensorOn = false;
    }
  }
}

