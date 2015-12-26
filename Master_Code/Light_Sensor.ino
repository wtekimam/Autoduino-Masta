
// -------------------------- //
// FUNCTIONS FOR LIGHT SENSOR //
// -------------------------- //

// LIGHT SENSOR FUNCTIONS:
// 1. checkLightMeter : check light meter every 1 second and turn on motion if dark enough

void checkLightMeter(){
  lux = lightMeter.readLightLevel();
  
    if (lux < 15) {
    motionOn = true;
    checkMovement();
  }
  else
    motionOn = false;

  delay(1000);
}
