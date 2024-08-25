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

const int PAUSE_DURATION = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = digitalRead(BUTTON_PIN);
  Serial.println("Gelesener Wert des digitalen PINs " + String(BUTTON_PIN) + " ist " + String(value));
  if (value == 1) digitalWrite(LED_PIN, LOW); else digitalWrite(LED_PIN, HIGH);
  delay(PAUSE_DURATION);
}
