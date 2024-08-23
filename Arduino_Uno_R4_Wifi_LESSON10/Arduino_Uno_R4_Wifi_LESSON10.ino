/**
 * Schaltplan:
 *   .---------.
 *   |         |10     //         ___
 *   | Arduino |------->|--------|___|------.
 *   | Uno R4  |                   1k       |
 *   | Wifi    |GND                         |
 *   |         |----------------------------'
 *   '---------'
 *
 * Die digital PINs mit dem vorangestellten Zeichen "~" können auch analog angesteuert werden, 
 * also: 11, 10, 9, 6, 5 und 3.
 */

const int ANALOG_LED_PIN = 10;
const int FULL_BRIGHTNESS = 255;
const int SERIAL_BAUD_RATE = 9600;
const int TURNING_POINT_DELAY = 1000;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(ANALOG_LED_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i <= FULL_BRIGHTNESS; i++) setBrightness(i);
  delay(TURNING_POINT_DELAY);
  for (int i = FULL_BRIGHTNESS; i >= 0; i--) setBrightness(i);
  delay(TURNING_POINT_DELAY);
}

void setBrightness(int brightness) {
  analogWrite(ANALOG_LED_PIN, brightness);
  Serial.println("Helligkeit der LED an analogen PIN " + String(ANALOG_LED_PIN) + " ist " + String(brightness));
}
