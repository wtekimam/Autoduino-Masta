
// -------------------------- //
// FUNCTIONS FOR LIGHT SENSOR //
// -------------------------- //

// LIGHT SENSOR FUNCTIONS:
// 1. checkLightMeter : check light meter every 1 second and turn on motion if dark enough

void checkLightMeter() {
  if (allSensorOn) {
    lux = lightMeter.readLightLevel();

    if (lux < 15) {
      motionOn = true;
      checkMovement();
    }
    else {
      motionOn = false;
      Serial.println(lux);
    }
    delay(50);
  }
}

