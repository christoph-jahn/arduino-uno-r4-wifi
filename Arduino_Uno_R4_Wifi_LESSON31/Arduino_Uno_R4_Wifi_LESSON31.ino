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
 *   |           _/|                 _______
 *   |          |5V o---------------o       |
 *   |         _|_/|                |       |
 *   |         |~11 o---------------o DHT11 |
 *   |         |__/|                |       |
 *   |             |                o       |
 *   |             |GND             |       |
 *   |             |----------------o_______|
 *   '-------------'
 *
 */

#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT11

DHT myDHT(DHTPIN, DHTTYPE);

const int SERIAL_BAUD_RATE = 115200;

const int SETUP_DELAY = 1000;
const int MEASUREMENT_DELAY = 1000;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  myDHT.begin();
  delay(SETUP_DELAY);
}

void loop() {
  float temperatureCelsius = myDHT.readTemperature(false);
  float temperatureFahrenheit = myDHT.readTemperature(true);
  float humidity = myDHT.readHumidity();
  if (isnan(temperatureCelsius) || isnan(temperatureFahrenheit) || isnan(humidity)) {
    Serial.println("Lesen der Daten vom DHT11 ist fehlgeschlagen.");
    return;
  }

  float heatIndexC = myDHT.computeHeatIndex(temperatureCelsius, humidity, false);
  float heatIndexF = myDHT.computeHeatIndex(temperatureFahrenheit, humidity, true);

  String message = "Temperatur: " + String(temperatureCelsius) + " °C (" + String(temperatureFahrenheit) + " °F); "
    + "Luftfeuchtigkeit: " + String(humidity) + " %; "
    + "Hitzeindex: " + String(heatIndexC) + " °C (" + String(heatIndexF) + " °F)";
  Serial.println(message);
  
  delay(MEASUREMENT_DELAY);
}
