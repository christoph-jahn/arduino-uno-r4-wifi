/**
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

const int RED_LED_PIN = 11;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 9;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

}

void loop() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
}
