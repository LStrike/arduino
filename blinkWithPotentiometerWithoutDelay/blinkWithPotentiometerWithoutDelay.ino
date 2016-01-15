/*
  Runninglight withoud delay with potentiomenter and serial output of the analog value (0 - 1023) and the corresponding voltage
 Connect the potentiometer to 5V
 
 This example code is in the public domain.
 Based on http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;
//the delay
int pause = 1500;
//count to decide which LEDs are HIGH and which are LOW
int count = 0;
// will store last time LED was updated
unsigned long previousMillis = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  unsigned long currentMillis = millis();

  // read the input on analog pin 0:
  pause = analogRead(A0);
  float voltage = pause * (5.0 / 1023.0);

  // print out the value and teh corresponding voltage you read:
  //Serial.println("Value: %d and Voltage: %f", pause, voltage);
  Serial.print("Value: ");
  Serial.println(pause);
  Serial.print("Volts: ");
  Serial.println(voltage);

  if (currentMillis - previousMillis >= pause) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if (count == 0) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
    } 
    else if (count == 1){
      digitalWrite(led2, HIGH);
    } 
    else if (count == 2) {
      digitalWrite(led1, LOW);
      digitalWrite(led3, HIGH);
    } 
    else if (count == 3) {
      digitalWrite(led2, LOW);
      digitalWrite(led4, HIGH);
    } 
    else if (count == 4) {
      digitalWrite(led3, LOW);
      digitalWrite(led5, HIGH);
    } 
    else if (count == 5) {
      digitalWrite(led4, LOW);
    } 
    else if (count == 6) {
      digitalWrite(led4, HIGH);
    } 
    else if (count == 7) {
      digitalWrite(led5, LOW);
      digitalWrite(led3, HIGH);
    } 
    else if (count == 8) {
      digitalWrite(led4, LOW);
      digitalWrite(led2, HIGH);
    } 
    else if (count == 9) {
      digitalWrite(led3, LOW);
      digitalWrite(led1, HIGH);
    } 
    else if (count == 10) {
      digitalWrite(led2, LOW);
      digitalWrite(led1, HIGH);
      count = -1;
    }
    count++;
  }
}



