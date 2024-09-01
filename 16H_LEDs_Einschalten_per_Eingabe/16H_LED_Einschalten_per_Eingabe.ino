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
 *   |         |GND
 *   |         |---------------------------.
 *   |         |                           |
 *   |         |~11    // (rot)  ___       |
 *   | Arduino |------->|-------|___|------o
 *   | Uno R4  |                  1k       |
 *   | Wifi    |~10    // (gelb) ___       |
 *   |         |------->|-------|___|------o
 *   |         |                  1k       |
 *   |         |~9     // (grün) ___       |
 *   |         |------->|-------|___|------'
 *   |         |                  1k
 *   '---------'
 *
 * Die digital PINs mit dem vorangestellten Zeichen "~" (PMW) können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 */

const int SERIAL_BAUD_RATE = 9600;
const int POLLING_DELAY = 100;

const int RED_LED_PIN = 11;
const int YELLOW_LED_PIN = 10;
const int GREEN_LED_PIN = 9;
const int INVALID_PIN = -1;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  analogWrite(RED_LED_PIN, 0);
  analogWrite(YELLOW_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 0);
}

void loop() {
  int pin = INVALID_PIN; while (pin == INVALID_PIN) pin = promptColor();
  int brightness = promptBrightness();
  analogWrite(pin, brightness);
}

int promptColor() {
  Serial.print("Welche LED soll leuchten (rot, grün, gelb): ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  String input = Serial.readString();
  Serial.println(input);

  input.toLowerCase();
  if (input == "rot") return RED_LED_PIN;
  else if (input == "grün") return GREEN_LED_PIN;
  else if (input == "gelb") return YELLOW_LED_PIN;
  Serial.println("Eine LED mit der Farbe " + input + " ist nicht bekannt.");
  return INVALID_PIN;
}

int promptBrightness() {
  Serial.print("Wie hell soll die LED leuchten (0-10): ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  int input = Serial.parseInt();
  Serial.println(input);
  int sanitizedInput = max(min(input, 10), 0);
  return pow(2, sanitizedInput / 10.0 * 8.0) - 1;
}
