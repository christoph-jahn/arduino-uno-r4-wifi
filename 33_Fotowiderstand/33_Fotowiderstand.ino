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
 *   .---------.
 *   |         |5V        ___
 *   | Arduino |---------|_x_|-----.
 *   | Uno R4  |          //       |
 *   | Wifi    |                   |
 *   |         |A0                 |
 *   |         |-------------------o
 *   |         |                   |
 *   |         |GND      ____      |
 *   |         |--------|____|-----'
 *   |         |             10k
 *   '---------'
 *
 */

const int LIGHT_PIN = A0;

void setup() {
  Serial.begin(115200);
  pinMode(LIGHT_PIN, INPUT);
}

void loop() {
  int lightValue = analogRead(LIGHT_PIN);

  // öffne "Serieller Plotter" (Symbol rechts oben in der Arduino IDE neben dem seriellen Monitor Button)
  Serial.print(lightValue);

  // die folgenden Zeilen deaktiviert auto-scaling im seriellen Plotter:
  Serial.print(',');
  Serial.print(0);
  Serial.print(',');
  Serial.println(1023);
  delay(100);
}
