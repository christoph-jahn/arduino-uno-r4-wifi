/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "11500 Baud"
 * 
 * Mit dem "Reset"-Taster auf der Arduino-Platine starte das Programm neu.
 * 
 * Schaltplan:
 *   .---------.                            _______
 *   |         |A1                   Orange|       |
 *   |         |---------------------------|       |
 *   |         |                           |       |
 *   |         |5V                      Rot|       |
 *   | Arduino |------o--------------------| Servo |
 *   | Uno R4  |      |   ___              | SG90  |
 *   | Wifi    |      '--|_x_|-----.       |       |
 *   |         |A0         //      |       |       |
 *   |         |-------------------o       |       |
 *   |         |          ____     |       |       |
 *   |         |      .--|____|----'       |       |
 *   |         |GND   |       10k   Schwarz|       |
 *   |         |------o--------------------|_______|
 *   '---------'
 *
 */
#include <Servo.h> // from Michael Margolis (v1.2.2)

const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 100;

const int LIGHT_PIN = A0;
const int SERVO_PIN = A1;

Servo servo;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(LIGHT_PIN, INPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  int lightValue = analogRead(LIGHT_PIN);

  int angle = 180. * lightValue / 1023.;
  servo.write(angle);

  delay(POLLING_TIME);
}
