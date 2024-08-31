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
 *   #---|___|---#-----------o |
 *   |5V         |             |=| (gelb)
 *   |           #-----------o |
 *   |           |GND
 *   |           |
 *   '-----------'           
 * 
 * Entscheidend ist hier der PIN-Modus "INPUT_PULLUP", der den PIN 13
 * mit einem Pullup-Widerstand, also einen Widerstand an 5V, verbindet.
 * Das bedeutet, bei gedrücktem Taster hat PIN 13 den Wert 0, sonst 1.
 *
 * WICHTIG: Arduino hat keinen eingebauten Pulldown-Widerstand. 
 * D.h. ein (externer) 10k Widerstand muss an Masse angeschlossen werden:
 *   .---------.
 *   |         |GND   ____
 *   | Arduino |-----|____|-------.
 *   | Uno R4  |       10k        |
 *   | Wifi    |2                 |    
 *   |         |------------------o |
 *   |         |                    |=| (rot)
 *   |         |                  o |
 *   |         |5V                |
 *   |         |------------------'
 *   '---------'
 */


const int PULLUP_YELLOW_BUTTON_PIN = 13;
const int PULLDOWN_RED_BUTTON_PIN = 2;
const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(PULLUP_YELLOW_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PULLDOWN_RED_BUTTON_PIN, INPUT);
}

void loop() {
  int yellowValue = digitalRead(PULLUP_YELLOW_BUTTON_PIN);
  Serial.print("Gelber Pullup Taster: " + String(yellowValue) + ", ");

  int redValue = digitalRead(PULLDOWN_RED_BUTTON_PIN);
  Serial.println("Roter Pulldown Taster: " + String(redValue));

  delay(POLLING_TIME);
}
