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
 *   .---------.                 .-------.
 *   |         |5V            Rot|       |
 *   | Arduino |--------o--------|       |
 *   | Uno R4  |       _|_       |       |
 *   | Wifi    |A2    |   |      |       |
 *   |         |----->|Pot|      | Servo |
 *   |         |      |___|      | SG90  |
 *   |         |GND     | Schwarz|       |
 *   |         |--------o--------|       |
 *   |         |                 |       |
 *   |         |~9         Orange|       |
 *   |         |-----------------|       |
 *   '---------'                 '-------'
 *
 * Die digitalen PINs mit dem vorangestellten Zeichen "~" (PWM) können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 *
 * 
 */
#include <Servo.h> // from Michael Margolis (v1.2.2)

const int POLLING_TIME = 100;
const int POTENTIOMETER_PIN = A2;
const int POTENTIOMETER_MAX = 1023;
const int SERIAL_BAUD_RATE = 115200;
const int SERVO_PIN = 9;
const int SERVO_WAIT = 50;

int angle;
Servo servo;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(POTENTIOMETER_PIN, INPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  delay(POLLING_TIME);
  int measurement = analogRead(POTENTIOMETER_PIN);
  if (!updateAngle(measurement)) return;

  Serial.println("Potentiometer: " + String(measurement));
  Serial.println("Winkel:        " + String(angle));
  servo.write(angle);
}

bool updateAngle(int measurement) {
  int currentAngle = 180. * measurement / POTENTIOMETER_MAX;
  bool angleHasChanged = currentAngle - angle != 0;
  if (angleHasChanged) angle = currentAngle; 
  return angleHasChanged;
}
