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
 *   | R4 Wifi             |
 *   |                   __|                          Blau
 *   |                  |4 o------------------------o |
 *   |                  |_/|                  Grün    |=|
 *   |                  |3 o---------------o |      o |
 *   |                  |_/|        Rot      |=|    |
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
 * Drei Taster mit drei verschiedenen Farben.
 */

const int RED_BUTTON_PIN = 2;
const int GREEN_BUTTON_PIN = 3;
const int BLUE_BUTTON_PIN = 4;

const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 50;

int redButtonValue = 1;
int greenButtonValue = 1;
int blueButtonValue = 1;

int redLedState = LOW;
int greenLedState = LOW;
int blueLedState = LOW;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP); pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP); pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP); pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  updateLedState(RED_BUTTON_PIN, redButtonValue, RED_LED_PIN, redLedState);
  updateLedState(GREEN_BUTTON_PIN, greenButtonValue, GREEN_LED_PIN, greenLedState);
  updateLedState(BLUE_BUTTON_PIN, blueButtonValue, BLUE_LED_PIN, blueLedState);
  delay(POLLING_TIME);
}

void updateLedState(int buttonPin, int& buttonOldValue, int ledPin, int& ledState) {
  int buttonNewValue = digitalRead(buttonPin);
  if (buttonOldValue == 1 && buttonNewValue == 0) {
    if (ledState == 1) digitalWrite(ledPin, LOW);
    if (ledState == 0) digitalWrite(ledPin, HIGH);
    ledState = !ledState;
  }
  buttonOldValue = buttonNewValue;
}
