/* AUTOMATIODUINO 0.1
 *  FOR 1 LIGHT (Pin 13)
 *  
 *  Functions include: 
 *    1. Motion sensor (pin 2)
*/

// defining pins
const unsigned int pirPin = 2; // Light sensor
const unsigned int lightPin = 13; // Output for light

bool sensorDetect;

// VARIABLES FOR MOTION SENSOR
int offTimer = 60; // time in secs before sensor would have to be retriggered
int countdown = offTimer; // for countdown of timer

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(lightPin, OUTPUT);

  digitalWrite(lightPin, LOW);

  Serial.begin(9600);
}

void loop() {
  checkMovement();
}

// --------------------------- //
// FUNCTIONS FOR MOTION SENSOR //
// --------------------------- //

// MOTION SENSOR FUNCTIONS: 
// 1. lightOn()     : countdown until light turns off
// 2. lightOff()    : to turn off the light
// 3. checkMovement : to check for movement

void lightOn() {
  for (countdown = offTimer; countdown > 0; countdown--) {
    digitalWrite(lightPin, HIGH);
    checkMovement();

    Serial.println(countdown);
    delay(1000);
  }

  Serial.println("Go to lightOff()");
  lightOff();
}

void lightOff() {
  digitalWrite(lightPin, LOW);

  checkMovement();
}

void checkMovement() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("go to lightOn()");

    lightOn();
  }
}

