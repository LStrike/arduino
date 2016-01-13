/*
  Runninglight with potentiomenter and serial output of the analog value (0 - 1023) and the corresponding voltage
  Connect the potentiometer to 5V
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;
int pause = 50;

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
  
  // read the input on analog pin 0:
  pause = analogRead(A0);
  float voltage= pause * (5.0 / 1023.0);
  
  // print out the value and teh corresponding voltage you read:
  //Serial.println("Value: %d and Voltage: %f", pause, voltage);
  Serial.print("Value: ");
  Serial.println(pause);
  Serial.print("Volts: ");
  Serial.println(voltage);
  
  
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(pause);  // wait for a second
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
