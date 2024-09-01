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
  Serial.println();
  for (int i = 0; i <= FULL_BRIGHTNESS; i++) setBrightness(i);
  delay(TURNING_POINT_DELAY);

  Serial.println();
  for (int i = FULL_BRIGHTNESS; i >= 0; i--) setBrightness(i);
  delay(TURNING_POINT_DELAY);
}

void setBrightness(int brightness) {
  analogWrite(ANALOG_LED_PIN, brightness);
  Serial.print("Helligkeit der LED am analogen PIN " + String(ANALOG_LED_PIN) + " ist " + String(brightness) + ". ");
  float percentage = 1.0 * brightness / FULL_BRIGHTNESS;
  float voltage = 5.0 * percentage;
  int onDuration = 2000 * percentage;
  int offDuration = 2000 - onDuration;
  Serial.print("Mittels PWM modulierte Spannung ist " + String(voltage) + "V, ");
  Serial.println("bzw. " + String(onDuration) + "µs lang 5V und " + String(offDuration) + "µs lang 0V.");
}
