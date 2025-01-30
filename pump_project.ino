
const int length = 10;
int lastVal[length];
int oldVal;
int buffer;

/*
  
*/
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {

  //Serial.println(String(updateMean()) + "  " + String(analogRead(A1)));
  checkSoil();
  checkLight();
  delay(100);
}

void checkSoil(){
  Serial.println(analogRead(A0));
  if(analogRead(A0) > 750){
    digitalWrite(8, HIGH);
  }
  else{
    digitalWrite(8, LOW);
  }

}

void checkLight(){
  if(updateMean() + buffer > 800){
    digitalWrite(12, HIGH);
    buffer = 150;
    

  }
  else{
    digitalWrite(12, LOW);
    buffer = 0;
    
  }

}


int updateMean() {

  int sum = 0;
  lastVal[length-1] = analogRead(A1);
  for (int i = 1; i < length; i++) {
    lastVal[i - 1] = lastVal[i];
  }
  for (int i = 0; i < length; i++) {
    sum += lastVal[i];
  }
  return sum / length;
}