/*
  File: pump_project.ino
  Author: Alexander Bohre
  Date: 2025-02-05
  Description: script for automatic plant system that brings light and water to plants automaticly.
*/

// Init constants
const int length = 10;

//initialising global variables
int lastVal[length];
int oldVal;
int threshold;            // Threshold to prevent light flickering.
bool finished = false;
int pumpTime = 10000;

void setup() {
  Serial.begin(9600);
  finished = false;

  //Setup input/output pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  checkSoil();
  checkLight();
  delay(100);
}

/*
  Caluclates the moisture of soil with input from A0
  Parameters: Void
  Returns: HIGH/LOW voltage on pin 8
*/
void checkSoil() {

  if (analogRead(A0) > 750 && !finished) {  // Read the value of soil moisture


    //pin 8 HIGH for 10s
    digitalWrite(8, HIGH);
    delay(pumpTime);
    digitalWrite(8, LOW);

    finished = true;                        //prevent from activation of pin 8
  } else if (analogRead(A0) < 650) {
    finished = false;                       // Allow activation for pin 8
  }
}

/*
  Caluclates the light with input from A1 
  Parameters: Void
  Returns: HIGH/LOW voltage on pin 12 and changes the global variable buffer if light is detected
*/
void checkLight() {

  // Takes value from updateMean

  if (updateMean() + threshold > 950) {
    digitalWrite(12, HIGH);
    threshold = 100;
  } else {
    digitalWrite(12, LOW);
    threshold = 0;
  }
}

/*
  Calculate the average input of integers with a shifting register low pass filter.
  Parameters: void
  Returns: returns an average of "length" amounts of inputs from A1.  
*/
int updateMean() {

  // shifting register that updates the array "lastVal"
  int sum = 0;
  lastVal[length - 1] = analogRead(A1);
  for (int i = 1; i < length; i++) {
    lastVal[i - 1] = lastVal[i];
  }

  // Calculating the total sum of the array "lastVal"
  for (int i = 0; i < length; i++) {
    sum += lastVal[i];
  }
  return sum / length;  // Calculates the average of sum
}