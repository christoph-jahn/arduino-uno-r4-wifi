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

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int MEASUREMENT_DELAY = 1000;
const int PULLUP_BUTTON_PIN = 12;
const int SERIAL_BAUD_RATE = 115200;
const int SETUP_DELAY = 1000;

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin(); delay(SETUP_DELAY);
  pinMode(PULLUP_BUTTON_PIN, INPUT_PULLUP);
  matrix.begin();
}

void loop() {
  while (digitalRead(PULLUP_BUTTON_PIN) == 0);
  while (digitalRead(PULLUP_BUTTON_PIN) == 1);

  String message = readFromDth();
  showText(message);
}

String readFromDth() {
  float temperatureCelsius;
  float temperatureFahrenheit;
  float humidity;
  bool invalidReading;

  do {
    temperatureCelsius = dht.readTemperature(false);
    temperatureFahrenheit = dht.readTemperature(true);
    humidity = dht.readHumidity();
    invalidReading = isnan(temperatureCelsius) || isnan(temperatureFahrenheit) || isnan(humidity);
    if (invalidReading) {
      Serial.println("Lesen der Daten vom DHT11 ist fehlgeschlagen.");
      delay(MEASUREMENT_DELAY);
    }
  } while (invalidReading);

  float heatIndexC = dht.computeHeatIndex(temperatureCelsius, humidity, false);
  float heatIndexF = dht.computeHeatIndex(temperatureFahrenheit, humidity, true);

  return "Luftfeuchtigkeit: " + String(humidity) + "% "
    + "Temperatur: " + String(temperatureCelsius) + "°C (" + String(temperatureFahrenheit) + "°F) "
    + "Hitzeindex: " + String(heatIndexC) + "°C (" + String(heatIndexF) + "°F)";
}

void showText(String text) {
  matrix.beginDraw();
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 255, 0, 0);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}
