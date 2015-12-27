
// --------------------------- //
// FUNCTIONS FOR MOTION SENSOR //
// --------------------------- //

// MOTION SENSOR FUNCTIONS:
// 1. lightOn()     : countdown until light turns off
// 2. lightOff()    : to turn off the light
// 3. checkMovement : to check for movement

void lightOn() {
  if (motionOn && allSensorOn) {
    countdown = offTimer;
    while (countdown > 0) {
      digitalWrite(lightPin, HIGH);
      checkMovement();

      Serial.println(countdown);
      readKeyInput();
      delay(1000);
      if (countdown > 0)
        countdown--;
    }

    Serial.println("Go to lightOff()");
    lightOff();
  }
}

void lightOff() {
  digitalWrite(lightPin, LOW);
  readKeyInput();
  checkLightMeter();
}

void checkMovement() {

  if (digitalRead(pirPin) == HIGH && motionOn && allSensorOn) {
    Serial.println("go to lightOn()");

    lightOn();
  }
}
