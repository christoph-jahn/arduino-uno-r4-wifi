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
 *   |         |13     // (rot)  ___
 *   | Arduino |------->|-------|___|------.
 *   | Uno R4  |                  1k       |
 *   | Wifi    |12     // (grün) ___       |
 *   |         |------->|-------|___|------o
 *   |         |                  1k       |
 *   |         |11     // (gelb) ___       |
 *   |         |------->|-------|___|------o
 *   |         |                  1k       |
 *   |         |GND                        |
 *   |         |---------------------------'
 *   '---------'
 */

const int SERIAL_BAUD_RATE = 9600;
const int POLLING_DELAY = 100;

const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;
const int YELLOW_LED_PIN = 11;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  turnAllOff();
}

void loop() {
  String color = promptColor();
  
  turnAllOff();
  if (color == "rot") digitalWrite(RED_LED_PIN, HIGH);
  else if (color == "grün") digitalWrite(GREEN_LED_PIN, HIGH);
  else if (color == "gelb") digitalWrite(YELLOW_LED_PIN, HIGH);
}

void turnAllOff() {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
}

String promptColor() {
  Serial.print("Welche LED soll leuchten (rot, grün, gelb): ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  String input = Serial.readString();
  Serial.println(input);

  input.toLowerCase();
  return input;
}
