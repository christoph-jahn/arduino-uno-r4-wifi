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

const int RED_BUTTON_PIN = 2;
const int GREEN_BUTTON_PIN = 3;
const int BLUE_BUTTON_PIN = 4;

const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

const int SERIAL_BAUD_RATE = 115200;

const int POLLING_TIME = 100;

const int BUTTON_RELEASED = 1;

int redState = LOW;
int greenState = LOW;
int blueState = LOW;

bool redReleased;
bool greenReleased;
bool blueReleased;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  pinMode(RED_BUTTON_PIN, INPUT);
  pinMode(GREEN_BUTTON_PIN, INPUT);
  pinMode(BLUE_BUTTON_PIN, INPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, redState);
  digitalWrite(GREEN_LED_PIN, greenState);
  digitalWrite(BLUE_LED_PIN, blueState);

  redReleased = isButtonReleased(RED_BUTTON_PIN);
  greenReleased = isButtonReleased(GREEN_BUTTON_PIN);
  blueReleased = isButtonReleased(BLUE_BUTTON_PIN);
}

void loop() {
  bool redUnchanged = true;
  bool greenUnchanged = true;
  bool blueUnchanged = true;
  while (redUnchanged && greenUnchanged && blueUnchanged) {
    redUnchanged = isButtonReleased(RED_BUTTON_PIN) == redReleased;
    greenUnchanged = isButtonReleased(GREEN_BUTTON_PIN) == greenReleased;
    blueUnchanged = isButtonReleased(BLUE_BUTTON_PIN) == blueReleased;
    delay(POLLING_TIME);
  }

  if (!redUnchanged) {
    redReleased = !redReleased;
    if (redReleased) redState = toggleLED(RED_LED_PIN, redState);
  }

  if (!greenUnchanged) {
    greenReleased = !greenReleased;
    if (greenReleased) greenState = toggleLED(GREEN_LED_PIN, greenState);
  }

  if (!blueUnchanged) {
    blueReleased = !blueReleased;
    if (blueReleased) blueState = toggleLED(BLUE_LED_PIN, blueState);
  }
}

bool isButtonReleased(int buttonPin) {
  return digitalRead(buttonPin) == BUTTON_RELEASED;
}

bool toggleLED(int ledPin, bool state) {
  digitalWrite(ledPin, !state);
  return !state;
}
