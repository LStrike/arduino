/*
 * LStrike - 2018
 * Indoor 
 * ESP8266 (D1 Mini)
 * OLED (I2C)
 * BH1750 (I2C)
 * BME280 (I2C)
 */

//ESP8266 WiFi
#include <ESP8266WiFi.h>
const char* ssid = "Eternia";
const char* password = "xXx";

//OLED - 0x3C
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0
Adafruit_SSD1306 OLED(OLED_RESET);
int address_oled = 60;

//BME280 - 0x76
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
Adafruit_BME280 bme; // I2C
float h, t, p, pin, dp;
char temperatureFString[6];
char dpString[6];
char humidityString[6];
char pressureString[7];
char pressureInchString[6];
int address_bme = 118;

//BH1750 - 0x23
#include <BH1750.h>
BH1750 lightMeter;
uint16_t lux;

//I2C
#include <Wire.h>

//Date and time
#include <WiFiUdp.h>
#include <WString.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "de.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String date;
String timeString;
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
const char * ampm[] = {"AM", "PM"} ;


void setup() {
  Serial.begin(115200);
  delay(10);

  timeClient.begin();   // Start the NTP UDP client

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Printing the ESP IP address
  Serial.println(WiFi.localIP());

  Serial.println(F("BME280 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
  
  // put your setup code here, to run once:
  OLED.begin();
  OLED.clearDisplay();
  OLED.setTextWrap(true);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println(" Welcome \n\t Michaela \n \t\t& \n \tMarkus ");
  OLED.display();


}

void getWeather() {
  
    h = bme.readHumidity();
    t = bme.readTemperature();
   // t = t*1.8+32.0;
    dp = t-0.36*(100.0-h);
    
    p = bme.readPressure()/100.0F;
    pin = 0.02953*p;
    dtostrf(t, 5, 1, temperatureFString);
    dtostrf(h, 5, 1, humidityString);
    dtostrf(p, 6, 1, pressureString);
    dtostrf(pin, 5, 2, pressureInchString);
    dtostrf(dp, 5, 1, dpString);
    delay(100);
 
}

void getLight(){
  lux = lightMeter.readLightLevel();
}

void printToDisplay(){
  OLED.clearDisplay();
  OLED.setTextWrap(true);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.print(date);
  OLED.print(timeString);
  OLED.print("\n");
  OLED.print("---------------------\n");
  OLED.print("Temperature: ");
  OLED.print(t);
  OLED.print(" C\n");
  OLED.print("Humidity: ");
  OLED.print(h);
  OLED.print(" %\n");
  OLED.print("Pressure: ");
  OLED.print(p);
  OLED.print(" hPa\n");
  OLED.print("Light: ");
  OLED.print(lux);
  OLED.print(" lx\n");
  
  OLED.display();
  
}

void getDateTime(){
    date = "";  // clear the variables
    timeString = "";
    
    // update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    unsigned long epochTime =  timeClient.getEpochTime();

    // convert received time stamp to time_t object
    time_t local, utc;
    utc = epochTime;

    // Then convert the UTC UNIX timestamp to local time
    TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, +60};  //UTC - 5 hours - change this as needed
    TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, +0};   //UTC - 6 hours - change this as needed
    Timezone usEastern(usEDT, usEST);
    local = usEastern.toLocal(utc);

    // now format the Time variables into strings with proper names for month, day etc
    date += days[weekday(local)-1];
    date += ", ";
    date += months[month(local)-1];
    date += " ";
    date += day(local);
    date += ", ";
    date += year(local);

    // format the time to 12-hour format with AM/PM and no seconds
    timeString += hourFormat12(local);
    timeString += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      timeString += "0";
    timeString += minute(local);
    timeString += " ";
    timeString += ampm[isPM(local)];
}

void loop() {
  // put your main code here, to run repeatedly:
  getWeather();
  getLight();
  getDateTime();

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("\n");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("\n");
  Serial.print("Pressure: ");
  Serial.print(p);
  Serial.print("\n");
  Serial.print("####################################\n");

  printToDisplay();
  
  delay(5000);

}
