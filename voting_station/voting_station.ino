/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*
   Thanks to Limor Fried / Ladyada for this example and for the library.
   Added code by LStrike / 2016-10-02
   Feel free to use this for your own purposes and have fun.

   BSD license, check license.txt for more information
   All text above, and the splash screen must be included in any redistribution
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// constants won't change. They're used here to
// set pin numbers:
const int button1Pin = 2;    // the number of the pushbutton pin 1
const int button2Pin = 4;    // the number of the pushbutton pin 2
const int button3Pin = 7;    // the number of the pushbutton pin 3
const int button4Pin = 8;    // the number of the pushbutton pin 4
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = LOW;         // the current state of the output pin

int button1State;             // the current reading from the input pin
int lastButton1State = LOW;   // the previous reading from the input pin

int button2State;
int lastButton2State = LOW;

int button3State;
int lastButton3State = LOW;

int button4State;
int lastButton4State = LOW;

boolean button1Pressed = false;
boolean button2Pressed = false;
boolean button3Pressed = false;
boolean button4Pressed = false;

String bic = "Powered by \nBIC Monitor";

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int count = 0;

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(1000);
  display.drawPixel(15, 10, WHITE);
  display.display();
  delay(1000);
  display.drawPixel(20, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Initializing");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println("BIC - Ver.: 0.0.2");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
  display.setTextColor(WHITE);
  display.println("Ready");
  display.setTextSize(1);
  display.println(bic);
  display.display();
  delay(2000);
  display.clearDisplay();

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

}


void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(button1Pin);
  int readingButton2 = digitalRead(button2Pin);
  int readingButton3 = digitalRead(button3Pin);
  int readingButton4 = digitalRead(button4Pin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButton1State || readingButton2 != lastButton2State || readingButton3 != lastButton3State || readingButton4 != lastButton4State) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != button1State) {
      button1State = reading;
      // only toggle the LED if the new button state is HIGH
      if (button1State == HIGH) {
        ledState = !ledState;
        button1Pressed = !button1Pressed;
        button2Pressed = false;
        button3Pressed = false;
        button4Pressed = false;
      }
    }
    if (readingButton2 != button2State) {
      button2State = readingButton2;
      if (button2State == HIGH) {
        button1Pressed = false;
        button2Pressed = !button2Pressed;
        button3Pressed = false;
        button4Pressed = false;
      }
    }
    if (readingButton3 != button3State) {
      button3State = readingButton3;
      if (button3State == HIGH) {
        button1Pressed = false;
        button2Pressed = false;
        button3Pressed = !button3Pressed;
        button4Pressed = false;
      }
    }

    if (readingButton4 != button4State) {
      button4State = readingButton4;
      if (button4State == HIGH) {
        button4Pressed = !button4Pressed;

        display.clearDisplay();

        if (button1Pressed) {
          Serial.println("1");
          display.println("Stimme fuer");
          display.println("Team 1");
          display.println("abgegeben");
        } else if (button2Pressed) {
          Serial.println("2");
          display.println("Stimme fuer");
          display.println("Team 2");
          display.println("abgegeben");
        } else if (button3Pressed) {
          Serial.println("3");
          display.println("Stimme fuer");
          display.println("Team 3");
          display.println("abgegeben");
        } else {
          //Serial.println("Status Button 1: OFF");
        }

        display.display();
        delay(5000);
        resetButtons();

      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);
  display.clearDisplay();
  if (button1Pressed && !button2Pressed && !button3Pressed) {
    display.println("Team 1 gewaehlt.");
    //display.println("Button 1 ON");
    //display.println("Button 2 OFF");
    //display.println("Button 3 OFF");
  } else if (!button1Pressed && button2Pressed && !button3Pressed) {
    display.println("Team 2 gewaehlt.");
    //display.println("Button 1 OFF");
    //display.println("Button 2 ON");
    //display.println("Button 3 OFF");
  } else if (!button1Pressed && !button2Pressed && button3Pressed) {
    display.println("Team 3 gewaehlt.");
    //display.println("Button 1 OFF");
    //display.println("Button 2 OFF");
    //display.println("Button 3 ON");
  } else if (!button1Pressed && !button2Pressed && !button3Pressed) {
    display.println("Bitte gebe Deine");
    display.println("Stimme fuer ein");
    display.println("Team ab.");
    display.println();
    display.println();
    display.println(bic);
  } else {
    display.println("BIC Monitor - S4M - NMM-ED");
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButton1State = reading;
  lastButton2State = readingButton2;
  lastButton3State = readingButton3;
  lastButton4State = readingButton4;
}

void resetButtons(void) {

  int lastButton1State = LOW;
  int lastButton2State = LOW;
  int lastButton3State = LOW;
  int lastButton4State = LOW;

  button1Pressed = false;
  button2Pressed = false;
  button3Pressed = false;
  button4Pressed = false;
}

