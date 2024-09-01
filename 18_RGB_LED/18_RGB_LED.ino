/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "115200 Baud"
 * 
 * Mit dem "Reset"-Taster auf der Arduino-Platine starte das Programm neu.
 *
 * Schaltplan:
 *   __________________
 *  |      RGB LED     |
 *  '------------------'
 *   R|  M|   G|    B|
 *    |   |    |     |
 *    |   |    |
 *        |
 *
 *   .---------.                     _____
 *   |         |~11    ___       Rot|     |
 *   | Arduino |------|___|---o-----|     |
 *   |         |        1k          |     |
 *   |         |GND              GND| RGB |
 *   |         |-------------o------| LED |
 *   | Uno R4  |                    |     |
 *   | Wifi    |~10    ___      Grün|     |
 *   |         |------|___|---o-----|     |
 *   |         |        1k          |     |
 *   |         |~9     ___      Blau|     |
 *   |         |------|___|----o----|     |
 *   |         |        1k          '-----'
 *   '---------'
 *
 * Die RGB LED hat vier Beine mit unterschiedlicher Länge. Masse ist der längste.
 *
 * Die digital PINs mit dem vorangestellten Zeichen "~" (PMW) können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 */

const int SERIAL_BAUD_RATE = 115200;
const int POLLING_DELAY = 100;

const int RED_LED_PIN = 11;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 9;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  Serial.print("Welche Farbe soll leuchten (rot, grün, blau, cyan, magenta, gelb, orange oder weiß): ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  String input = Serial.readString();
  Serial.println(input);

  // Farbtabelle verfügbar unter: https://htmlcolorcodes.com/colors/
  input.toLowerCase();
  if (input == "rot") setRGB(255, 0, 0);
  else if (input == "grün") setRGB(0, 255, 0);
  else if (input == "blau") setRGB(0, 0, 255);
  else if (input == "cyan") setRGB(0, 255, 255);
  else if (input == "magenta") setRGB(255, 0, 255);
  else if (input == "gelb") setRGB(255, 255, 0);
  else if (input == "orange") setRGB(255, 165, 0);
  else if (input == "weiß" || input == "weiss") setRGB(255, 255, 255);
  else Serial.println("Die Farbe " + input + " ist nicht bekannt.");
}

void setRGB(int red, int green, int blue) {
  analogWrite(RED_LED_PIN, red);
  analogWrite(GREEN_LED_PIN, green);
  analogWrite(BLUE_LED_PIN, blue);
}
