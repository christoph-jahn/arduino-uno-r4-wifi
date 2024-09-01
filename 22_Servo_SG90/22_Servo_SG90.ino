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
 *
 *   .---------.                _______
 *   |         |GND     Schwarz|       |
 *   | Arduino |---------------|       |
 *   |         |               |       |
 *   |         |5V          Rot| Servo |
 *   |         |---------------| SG90  |
 *   | Uno R4  |               |       |
 *   | Wifi    |~9       Orange|       |
 *   |         |---------------|       |
 *   |         |               '-------'
 *   '---------'
 *
 * Die digitalen PINs mit dem vorangestellten Zeichen "~" (PWM) können auch analog angesteuert werden, 
 * also: ~11, ~10, ~9, ~6, ~5 und ~3.
 */
#include <Servo.h> // from Michael Margolis (v1.2.2)

const int SERIAL_BAUD_RATE = 115200;
const int SERIAL_POLLING_TIME = 100;

const int SERVO_PIN = 9;
const int SERVO_WAIT = 50;
Servo servo;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  servo.attach(SERVO_PIN);
}

void loop() {
  // promptExample();
  loopExample();
}

void promptExample() {
  Serial.print("Gib den absoluten Winkel für den Servo ein: ");
  while (Serial.available() == 0) delay(SERIAL_POLLING_TIME);
  int angle = Serial.parseInt();
  Serial.println(angle);

  servo.write(angle);
}

void loopExample() {
  for (int angle = 0; angle < 180; angle++) {
    servo.write(angle);
    delay(SERVO_WAIT);
  }

  for (int angle = 180; angle > 0; angle--) {
    servo.write(angle);
    delay(SERVO_WAIT);
  }
}
