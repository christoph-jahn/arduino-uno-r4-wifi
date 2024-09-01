/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "115200 Baud"
 *
 * Der "Reset"-Taster auf der Arduino-Platine startet das Programm neu.
 *
 * Schaltplan:
 *   .-------------.
 *   | Arduino Uno |
 *   | R4 Wifi     |
 *   |         ___/|                  _______
 *   |        | 5V #-----------------#       |
 *   |        |___/|                 |       |
 *   |        |~11 #-----------------# DHT11 |
 *   |        |___/|                 |       |
 *   |             |                 #       |
 *   |         ___/|                 |       |
 *   |        |GND #--------o--------#_______|
 *   |        |___/|        |
 *   |             |        o |
 *   |      ______/|          |=|
 *   |     |12(PU) #--------o |
 *   |     |______/|
 *   |             |
 *   |             |
 *   |             |
 *   '-------------'
 *
 */

#include <DHT.h>
#define DHTPIN 11
#define DHTTYPE DHT11
DHT myDHT(DHTPIN,DHTTYPE);
 
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

const int SERIAL_BAUD_RATE = 115200;
const int setUpDelay = 1000;
const int measDelay = 1000;
 
float tempC;
float tempF;
float hum;
float HIF;
float HIC;
 
String message;

int butPin = 12;
int butVal = 1;
int butValOld = 1;
 
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  myDHT.begin();
  delay(setUpDelay);
  pinMode(butPin, INPUT_PULLUP);
  matrix.begin();
}
 
void loop() {
  butVal = digitalRead(butPin);
  if (butVal == 0 && butValOld == butVal == 1) {
    tempC=myDHT.readTemperature(false);
    tempF=myDHT.readTemperature(true);
    hum=myDHT.readHumidity();
    if (isnan(tempC) || isnan(tempF) || isnan(hum)){
      Serial.println("Failed to Read Data on DHT11");
      return;
    }
    HIC=myDHT.computeHeatIndex(tempC,hum,false);
    HIF=myDHT.computeHeatIndex(tempF,hum,true);
    message="Temp: "+String(tempC)+" deg C "+String(tempF)+" deg F Humidity: "+String(hum)+" % Heat Index: "+String(HIC)+" deg C "+String(HIF)+" deg F.";
    Serial.println(message);

    matrix.beginDraw();
    matrix.textScrollSpeed(75);
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 255, 0, 0);
    matrix.println(message);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();

    delay(measDelay);
  }

  butValOld = butVal;
}
