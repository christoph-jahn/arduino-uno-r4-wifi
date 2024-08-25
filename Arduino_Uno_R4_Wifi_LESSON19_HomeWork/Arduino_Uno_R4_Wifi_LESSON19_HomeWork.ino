/**
 * Mit dem "Reset"-Taster auf der Arduino-Platine startet das Programm neu.
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

const int RED_LED_PIN = 11;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 9;

const int WAIT_TIME = 1000;
const int BLINKING_DURATION = 100;

const int MAX_COUNT = 25;
int counter;

void setup() {
  counter = 0;
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  if (counter >= MAX_COUNT) return; else counter++;

  setRGB(255, 0, 0);
  setRGB(0, 255, 0);
  setRGB(0, 0, 255);
  setRGB(0, 0, 0);

  delay(WAIT_TIME);
}

void setRGB(int red, int green, int blue) {
  analogWrite(RED_LED_PIN, red);
  analogWrite(GREEN_LED_PIN, green);
  analogWrite(BLUE_LED_PIN, blue);
  delay(BLINKING_DURATION);
}
