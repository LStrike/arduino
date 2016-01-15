// Sketch re: http://arduino.stackexchange.com/questions/19605/running-light-without-delay-and-a-potentiometer

// Set constants for pins with LEDs
enum { 
  led1 = 13, led2 = 12, led3 = 11, led4 = 10, led5 = 9};

// Make an array with the LED pin numbers
byte ledPins[] = { 
  led1, led2, led3, led4, led5 };

// # of entries in ledPins:
enum { 
  numLeds = sizeof(ledPins) / sizeof ledPins[0]};

//count to track which LEDs are HIGH and which are LOW
int count = numLeds-1;      // Will roll over to 0

// To store last time LED was updated
unsigned long previousMillis = 0;

//direction forward
boolean forward = true;

void setup() {
  // initialize digital pin outputs
  for (byte i=0; i<numLeds; ++i)
    pinMode(ledPins[i], OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// loop() runs over and over again forever:
void loop() {
  unsigned long currentMillis = millis();
  // read input on analog pin 0:
  int deli = analogRead(A0);
  float voltage = deli * (5.0 / 1023.0);

  // Print out the value and corresponding voltage you read:
  // Serial.println("Value: %d and Voltage: %f", pause, voltage);
  // Serial.print("Value: ");
  // Serial.println(deli);
  // Serial.print("Volts: ");
  // Serial.println(voltage);

  if (currentMillis - previousMillis >= deli) {
    // Save the last time we blinked the LED
    previousMillis = currentMillis;

    if(forward){
      // Turn off current LED, turn on next one
      digitalWrite(ledPins[count], LOW);
      count = (count+1) % numLeds;
      digitalWrite(ledPins[count], HIGH);

      if(count == numLeds-1 ){
        forward = false;
        count = 0;
      }
    }
    else {
      digitalWrite(ledPins[count + numLeds-1], LOW);
      count = (count - 1) % numLeds;
      digitalWrite(ledPins[count + numLeds-1], HIGH);

      if(count + numLeds-1 == 0){
        forward = true;
        count = 0;
      }
    }
  }
}







