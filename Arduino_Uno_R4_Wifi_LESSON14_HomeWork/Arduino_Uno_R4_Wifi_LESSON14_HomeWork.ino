/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "9600 Baud"
 * 
 * Mit dem "Reset"-Taster auf der Arduino-Platine starte das Programm neu.
 * 
 * Schaltplan:
 *   .---------.
 *   |         |~11    //         ___
 *   | Arduino |------->|--------|___|------.
 *   | Uno R4  |                   1k       |
 *   | Wifi    |GND                         |
 *   |         |----------------------------'
 *   '---------'
 *
 * Die digital PINs mit dem vorangestellten Zeichen "~" können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 */

const int DIMMABLE_LED_PIN = 11;
const int SERIAL_BAUD_RATE = 9600;
const int INPUT_MIN = 0;
const int INPUT_MAX = 10;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(DIMMABLE_LED_PIN, OUTPUT);
}

void loop() {
  int userInput = promptForBrightness();
  int userInputSanitized = min(max(userInput, INPUT_MIN), INPUT_MAX);
  int brightness = pow(2, 8. * userInputSanitized / (INPUT_MAX - INPUT_MIN)) - 1;
  analogWrite(DIMMABLE_LED_PIN, brightness);
  Serial.print("Deine Eingabe war " + String(userInput));
  Serial.print(", nach Überprüfung " + String(userInputSanitized));
  Serial.println(", ergibt die Helligkeit " + String(brightness) + ".");
}

int promptForBrightness() {
  Serial.println("Gib einen Wert zwischen 0 und 10 für die Helligkeit der LED ein:");
  while (Serial.available() == 0) {}
  return Serial.parseInt();
}
