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
const int LED_PIN = 10;
const int SERIAL_BAUD_RATE = 115200;

const int POLLING_TIME = 100;

int ledState = LOW;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  while (digitalRead(BUTTON_PIN) == 0) delay(POLLING_TIME);
  if (ledState == LOW) ledState = HIGH; else ledState = LOW;

  while (digitalRead(BUTTON_PIN) == 1) delay(POLLING_TIME);
  digitalWrite(LED_PIN, ledState); 
}
