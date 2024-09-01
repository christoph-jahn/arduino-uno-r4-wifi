/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "9600 Baud"
 * 
 * Mit dem "Reset"-Taster auf der Arduino-Platine starte das Programm neu.
 */

const int SERIAL_BAUD_RATE = 9600;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  //integerExample();
  //floatExample();
  stringExample();
}

void integerExample() {
  Serial.println("Wie lautet deine Zahl?");
  while (Serial.available() == 0) {
  }

  int input = Serial.parseInt();
  Serial.println("  Deine Zahl lautet: " + String(input));
}

void floatExample() {
  Serial.println("Bitte gebe eine Fließkommazahl ein:");
  while (Serial.available() == 0) {
  }

  float input = Serial.parseFloat();
  Serial.println("  Deine Fließkommazahl ist: " + String(input));
}

void stringExample() {
  Serial.println("Wie heißt du?");
  while (Serial.available() == 0) {}

  String input = Serial.readString();
  Serial.println("  Hallo " + input + ", willkommen bei Arduino!");
}
