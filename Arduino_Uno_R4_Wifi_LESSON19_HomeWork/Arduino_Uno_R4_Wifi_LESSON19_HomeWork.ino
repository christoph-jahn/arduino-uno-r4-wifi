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
 * Die digital PINs mit dem vorangestellten Zeichen "~" (PWM) können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 */

const int SERIAL_BAUD_RATE = 115200;
const int SERIAL_POLLING_TIME = 100;

const int RED_LED_PIN = 11;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 9;

const int WAIT_TIME = 1000;
const int BLINKING_DURATION = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  Serial.print("Wie oft soll die RGB-Sequenz ausgeführt werden? ");
  while (Serial.available() == 0) { delay(SERIAL_POLLING_TIME); }
  int repetitions = Serial.parseInt();
  Serial.println(repetitions);

  int i = 0;
  while (i < repetitions) {
    runRgbSequence();
    i++;
  }
}

void runRgbSequence() {
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
