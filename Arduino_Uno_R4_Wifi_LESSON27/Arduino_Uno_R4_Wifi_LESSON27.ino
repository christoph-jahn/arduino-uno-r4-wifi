/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "115200 Baud"
 * 
 * Der "Reset"-Taster auf der Arduino-Platine startet das Programm neu.
 *
 * Schaltplan (PIN 13 im Modus "INPUT_PULLUP"):
 *   .-----------.
 *   |           |
 *   |  Arduino  |
 *   |  Uno R4   | 
 *   |    ___    |13(PU)   
 *   #---|___|---#------------------o |
 *   |5V         |                    |=|
 *   |           #------------------o |
 *   |           |GND
 *   |           |
 *   '-----------'           
 * 
 * Entscheidend ist hier der PIN-Modus "INPUT_PULLUP", der den PIN 13
 * mit einem Pullup-Widerstand, also einen Widerstand an 5V, verbindet.
 */


const int BUTTON_PIN = 13;
const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int buttonValue = digitalRead(BUTTON_PIN);
  Serial.println(buttonValue);
  delay(POLLING_TIME);
}
