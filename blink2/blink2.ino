/*
  running light
  Turns on an 5 LEDs, one after another, on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;
int pause = 50;

void setup() {                
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  digitalWrite(led1, HIGH);   
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led2, HIGH);
  delay(pause);
  digitalWrite(led1, LOW);
  digitalWrite(led3, HIGH);
  delay(pause);
  digitalWrite(led2, LOW);
  digitalWrite(led4, HIGH);
  delay(pause);
  digitalWrite(led3, LOW);
  digitalWrite(led5, HIGH);
  delay(pause);
  digitalWrite(led4, LOW);
  delay(pause);
  digitalWrite(led4, HIGH);
  delay(pause);
  digitalWrite(led5, LOW);
  digitalWrite(led3, HIGH);
  delay(pause);
  digitalWrite(led4, LOW);
  digitalWrite(led2, HIGH);
  delay(pause);
  digitalWrite(led3, LOW);
  digitalWrite(led1, HIGH);
  delay(pause);
  digitalWrite(led2, LOW);
}
