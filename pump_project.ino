/*
  File: pump_project.ino
  Author: Alexander Bohre
  Date: 2025-02-05
  Description: script for a automatic plant system that brings light and water to plants automaticly.
*/

//initialising global variables
const int length = 10; 
int lastVal[length];
int oldVal;
int threshold; // Threshold to prevent light flickering.
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

  // Calling functions
  checkSoil();
  checkLight();
  delay(100);
}
/*
  Caluclates the moisture of the soil with input from A0
  Parameters: Void
  Returns: HIGH/LOW voltage on pin 8
*/
void checkSoil(){
  Serial.println(analogRead(A0));

  if(analogRead(A0) > 500 && !finished){
    digitalWrite(8, HIGH);
    delay(pumpTime);
    digitalWrite(8, LOW);
    Serial.println("finished");
    finished = true;
  }
  else if (analogRead(A0) < 400){
    finished = false;
  }
 

}

/*
  Caluclates the light with input from A1 
  Parameters: Void
  Returns: HIGH/LOW voltage on pin 12 and changes the global variable buffer if light is detected
*/
void checkLight(){

  // Takes value from updateMean 

  if(updateMean() + threshold > 950){
    digitalWrite(12, HIGH);
    threshold = 100; 
    }
  else{
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
  lastVal[length-1] = analogRead(A1);
  for (int i = 1; i < length; i++) {
    lastVal[i - 1] = lastVal[i];
  }

  // Calculating the total sum of the array "lastVal"
  for (int i = 0; i < length; i++) {
    sum += lastVal[i];
  }
  return sum / length; // Calculates the average of sum
}