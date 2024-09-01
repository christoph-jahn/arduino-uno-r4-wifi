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
 *   .---------------------.
 *   | Arduino Uno         |
 *   | R4 Wifi          ___| 
 *   |                 |5V_o------o--------o--------.
 *   |                 |_/ |      |        |        |
 *   |                     |     .-.      .-.      .-.
 *   |                     |     | |10k   | |10k   | |10K
 *   |                     |     | |      | |      | |
 *   |                     |     '-'      '-'      '-'
 *   |                   __|      |        |        | Blau
 *   |                  |4 o------|--------|--------o |
 *   |                  |_/|      |        |  Grün    |=|
 *   |                  |3 o------|--------o |      o |
 *   |                  |_/|      | Rot      |=|    |
 *   |                  |2 o------o |      o |      |
 *   |                  |_/|        |=|    |        |
 *   |                     |      o |      |        |
 *   |___   ___   ___   __ |GND   |        |        |
 *   |~11| |~10| |GND| |~9||------o--------o--------'
 *   '-o-----o-----o----o--'
 *     |     |     |    |
 *    .-.   .-.    |   .-.
 *    | |1k | |1k  |   | |1k
 *    | |   | |    |   | |
 *    '-'   '-'    |   '-'
 *     |     |     |    |
 *    Blau  Grün  GND  Rot
 *   .---------------------.
 *   |       RGB LED       |
 *   '---------------------'
 *
 * Die Beine der RGB-LED sind unterschiedlich lang. GND ist das längste.
 * Drei Taster mit drei verschieben Farben.
 */

const int butPinR = 2;
const int butPinG = 3;
const int butPinB = 4;

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int br = 115200;

int butValOldR = 1;
int butValOldG = 1;
int butValOldB = 1;

int LEDstateR = LOW;
int LEDstateG = LOW;
int LEDstateB = LOW;

int dt = 50;

void setup() {
  Serial.begin(br);
  pinMode(butPinR, INPUT); pinMode(redPin, OUTPUT);
  pinMode(butPinG, INPUT); pinMode(greenPin, OUTPUT);
  pinMode(butPinB, INPUT); pinMode(bluePin, OUTPUT);
}

void loop() {
  int butValR = digitalRead(butPinR);
  int butValG = digitalRead(butPinG);
  int butValB = digitalRead(butPinB);

  LEDstateR = updateLEDstate(butValOldR, butValR, LEDstateR, redPin);
  LEDstateG = updateLEDstate(butValOldG, butValG, LEDstateG, greenPin);
  LEDstateB = updateLEDstate(butValOldB, butValB, LEDstateB, bluePin);

  butValOldR = butValR;
  butValOldG = butValG;
  butValOldB = butValB;
  delay(dt);
}

int updateLEDstate(int butValOld, int butVal, int LEDstate, int pin) {
  if (butValOld == 1 && butVal == 0) {
    if (LEDstate == 1) digitalWrite(pin, LOW);
    if (LEDstate == 0) digitalWrite(pin, HIGH);
    return !LEDstate;
  }
  return LEDstate;
}
