/*
   Created By: Tyler Thibault
   Created Date:


   Program Description:
   This program will take a series of imputs from a motion sensor and put them
   into an array in order to make a decision on whether or not there is movement.
   If there is movement then it will trigger a countdown timer. The countdown timer
   will continue to reset as long as there is movement in the room. If there is no
   movement then the countdown will continually decrees until it reaches 0. At that
   point the lights will then turn off and wait until there is more motion.

          SERIAL READ LAYOUT
    0 | 0 | 00000000 | 0 | 0 | LED: OFF/ON

  column 1: Current index being read
  column 2: current input from sensor
  column 3: the amount of reads within the threshold
  column 4: total number of TRUE statements within the threshold
  column 5: Amount of time on the Timer
  column 6: status of LED
*/

/////////////////////////////////////////////////
// VARS
/////////////////////////////////////////////////

int pinLed = 13;  //pin location for the LED
int sensPin = 2;  //pin location for the sensor module
int masterPin = 8; //pin location for the master button

int input;  //what is read from the sensor module

//Calabration Vars
int calibrationTime = 3;

//Threshold Vars
bool inputThreshold[10];  //change the # in the [] to increase/decrease the amount of reads taken per decision
int thresholdLimit = 4;  //the number of TRUE vars required before the light goes on
int indexCount;  //total number of # within the threshold
int index;  //the threshold bool that is currently being read

//Timer Vars
int timerTime = 10;  //the amount of time on the countdown timer, in seconds
int timerReset = timerTime;  //the ablility to reset the timer to the original time
bool timerOn = true;  //determines whether or not the timer should start

//Master Switch Vars
bool masterSwitch = true;


/////////////////////////////////////////////////
// SETUP
/////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(sensPin, INPUT);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  indexCount = sizeof(inputThreshold) / sizeof(inputThreshold[0]);  //determines how many index boxs there are in total
  inputThreshold[indexCount] = {0};

  calibration();
}

/////////////////////////////////////////////////
// MAIN LOOP
/////////////////////////////////////////////////

void loop() {
  //evaluateMasterPress();
  inputFunction();
  //This simulates the motionInput function when there is no motion sensor connected

  //motionInput(); //if inputFunction() is not commented out then this needs to be commented out


  //if (masterSwitch) {

  indexPrint();
  Serial.print(" | ");
  Serial.print(input);
  Serial.print(" | ");

  threshold();

  Serial.print(" | ");

  evaluationOfThreshold();

  timer();

  Serial.println();

  delay(250);

}

/////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////

void calibration() {
  Serial.println();
  Serial.println("Sensor is Calibrating");
  for (int i = calibrationTime; i > 0; i--) {
    Serial.print(i);
    Serial.print(" ");
    delay(1000);
  }
  Serial.println();
}

void indexPrint() {
  //simply trying to straighten up the index line when the index is greater than 10
  if (index < 10) {
    Serial.print(" ");
    Serial.print(index);
    //Serial.print(" ");
  }
  else {
    Serial.print(index);
  }
}

void evaluateMasterPress() {
  if (digitalRead(masterPin) == HIGH) {
    masterSwitch = !masterSwitch;
    Serial.print("Motion Sensor ");
    if (masterSwitch) {
      Serial.print("Armed");
      calibration();
    }
    else {
      Serial.print("Dearmed");
    }
    delay(1000);
    Serial.println();
  }
  if (masterSwitch == false) {
    digitalWrite(pinLed, LOW);
  }
}

void motionInput() {
  //Takes the input from the motion sensor and puts it into the input variable
  if (digitalRead(sensPin) == HIGH) {
    input = 1;
  }
  else {
    input = 0;
  }
}

void inputFunction() {
  //Simulates the motion sensor when the motion sensor is not connected
  input = random(2) == 1;
}

void threshold() {
  //puts the input value into the first threshold index or "bucket" then moves onto the next index
  inputThreshold[index] = input;

  for (int i = 0; i < indexCount; i++) {
    Serial.print(inputThreshold[i]);
  }


  index++;
  if (index >= indexCount) {
    index = 0;
  }
}

void evaluationOfThreshold() {
  //this will evaluate the out come of the # of TRUE variables within the threshold to make a decision
  int outcomeOfThreshold = 0;

  for (int i = 0; i < indexCount; i++) {
    if (inputThreshold[i]) {
      outcomeOfThreshold++;
    }
  }
  if (outcomeOfThreshold < 10) {
    Serial.print(" ");
  }
  
  Serial.print(outcomeOfThreshold);
  Serial.print(" | ");
  Serial.print(timerTime);
  
  if (timerTime < 10) {
    Serial.print(" ");  //add another space if the # is less than 10 to keep the readout smooth
  }
  
  Serial.print(" | ");

  if (outcomeOfThreshold >= thresholdLimit) {
    timerOn = true;
    digitalWrite(pinLed, HIGH);
    Serial.print("LED On");
    timerTime = timerReset;
  }
  else {
    digitalWrite(pinLed, LOW);
    Serial.print("LED Off");
  }
}

void timer() {
  //This is the timer function that when on, counts down from the set time to 0
  if (timerOn) {
    digitalWrite(pinLed, HIGH);
    timerTime--;
    if (timerTime <= 0) {
      timerOn = false;
      timerTime = timerReset;
    }
  }
}






