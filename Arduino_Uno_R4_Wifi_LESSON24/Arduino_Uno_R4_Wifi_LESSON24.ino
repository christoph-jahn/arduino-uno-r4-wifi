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
 *   |         |GND   ____
 *   | Arduino |-----|____|-----.
 *   | Uno R4  |       10k      |
 *   | Wifi    |2               |    
 *   |         |----------------o |
 *   |         |                  |=|
 *   |         |                o |
 *   |         |5V              |
 *   |         |----------------'
 *   '---------'           
 * 
 */


const int BUTTON_PIN = 2;
const int SERIAL_BAUD_RATE = 115200;

const int PAUSE_DURATION = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int value = digitalRead(BUTTON_PIN);
  Serial.println("Gelesener Wert des digitalen PINs " + String(BUTTON_PIN) + " ist " + String(value));
  delay(PAUSE_DURATION);
}
