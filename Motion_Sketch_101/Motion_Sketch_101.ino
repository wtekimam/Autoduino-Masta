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

*/

/////////////////////////////////////////////////
// VARS
/////////////////////////////////////////////////

int pinLed = 13;
int sensPin = 8;

int input;

//Threshold Vars
bool inputThreshold[10];
int thresholdLimit = 5;
int indexCount;
int index;

//Timer Vars
int timerTime = 10;
int timerReset = timerTime;
bool timerOn = false;



/////////////////////////////////////////////////
// SETUP
/////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(sensPin, INPUT);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  indexCount = sizeof(inputThreshold) / sizeof(inputThreshold[0]);
  inputThreshold[indexCount] = {0};
}

/////////////////////////////////////////////////
// MAIN LOOP
/////////////////////////////////////////////////

void loop() {
  //inputFunction();
  
  motionInput(); //when input is set to random motionInput function needs to be off
  Serial.print(input);

  Serial.print(" | ");
  threshold();
  Serial.print(" | ");
  
  evaluation();
  
  timer();

  Serial.println();
  delay(500);

}

/////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////

void motionInput() {
  //Takes the input from the motion sensor and puts it into a boolean var
  if (sensPin == HIGH) {
    input = 1;
  }
  else {
    input = 0;
  }
}

void inputFunction() {
  
  input = random(2) == 1;
}

void threshold() {
  inputThreshold[index] = input;

  for (int i = 0; i < indexCount; i++) {
    Serial.print(inputThreshold[i]);
  }


  index++;
  if (index >= indexCount) {
    index = 0;
  }
}

void evaluation() {
  int outcomeOfThreshold = 0;

  for(int i = 0;i < indexCount; i++){
    if(inputThreshold[i]){
      outcomeOfThreshold++;
    }
  }
  if(outcomeOfThreshold < 10){
    Serial.print(" ");
  }
  Serial.print(outcomeOfThreshold);
  Serial.print(" | ");

  if(outcomeOfThreshold >= thresholdLimit){
    timerOn = true;
    digitalWrite(pinLed, HIGH);
    Serial.print("LED On");
  }
  else{
    digitalWrite(pinLed, LOW);
    Serial.print("LED Off");
  }
}

void timer() {

  if(timerOn){
    digitalWrite(pinLed, HIGH);
    timerTime--;
    Serial.print(" ");
    Serial.print(timerTime);
    Serial.print(" ");
    if(timerTime <= 0){
      timerOn = false;
      timerTime = timerReset;
    }
  }
  else{
    
  }
}






