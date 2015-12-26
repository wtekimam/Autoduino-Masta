
// --------------------------- //
// FUNCTIONS FOR MOTION SENSOR //
// --------------------------- //

// MOTION SENSOR FUNCTIONS:
// 1. lightOn()     : countdown until light turns off
// 2. lightOff()    : to turn off the light
// 3. checkMovement : to check for movement

void lightOn() {
  if (motionOn) {
    for (countdown = offTimer; countdown > 0; countdown--) {
      digitalWrite(lightPin, HIGH);
      checkMovement();

      Serial.println(countdown);
      delay(1000);
    }

    Serial.println("Go to lightOff()");
    lightOff();
  }
}

void lightOff() {
  digitalWrite(lightPin, LOW);
  
  checkLightMeter();
  checkMovement();
}

void checkMovement() {
  
    if (digitalRead(pirPin) == HIGH && motionOn) {
      Serial.println("go to lightOn()");

      lightOn();
    }
}
