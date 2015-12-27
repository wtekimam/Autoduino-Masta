void readKeyInput() {
  key = kpd.getKey();
  if (key) { // only display key if key is pressed
    switch (key) {
      case 'A':
        allSensorOn = false;
        Serial.print("false ");
        Serial.println(key);
        lightOff();
        break;
      case 'B':
        allSensorOn = true;
        Serial.print("true ");
        Serial.println(key);
        break;
      default:
        Serial.println(key);
    }
  }
}

