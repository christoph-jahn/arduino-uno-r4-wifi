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
 *   .---------.
 *   |         |~10  //    ____
 *   |         |----->|---|____|--.
 *   |         |             1k   |
 *   |         |                  |
 *   |         |GND   ____        |
 *   | Arduino |-----|____|-------o
 *   | Uno R4  |       10k        |
 *   | Wifi    |2                 |    
 *   |         |------------------o |
 *   |         |                    |=|
 *   |         |                  o |
 *   |         |5V                |
 *   |         |------------------'
 *   '---------'           
 * 
 */


const int BUTTON_PIN = 2;
const int BUTTON_PRESSED = 0;
const int BUTTON_RELEASED = 1;
const int LED_PIN = 10;
const int SERIAL_BAUD_RATE = 115200;

const int POLLING_TIME = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, LOW); waitUntilButtonWasReleasedAndPressed();
  digitalWrite(LED_PIN, HIGH); waitUntilButtonWasReleasedAndPressed();
}

void waitUntilButtonWasReleasedAndPressed() {
  while (digitalRead(BUTTON_PIN) == BUTTON_PRESSED) delay(POLLING_TIME);
  while (digitalRead(BUTTON_PIN) == BUTTON_RELEASED) delay(POLLING_TIME);
}
