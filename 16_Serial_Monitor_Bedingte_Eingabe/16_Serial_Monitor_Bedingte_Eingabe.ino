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
const int POLLING_DELAY = 100;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  // numberExamples();
  colorExample();
}

void colorExample() {
  Serial.print("Gib eine Farbe ein: ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  String input = Serial.readString();
  Serial.println(input);

  input.toLowerCase();
  if (input == "rot") Serial.println("ROTER ALARM!!!");
  else Serial.println("Die Farbe ist " + input + ".");
}

void numberExamples() {
  Serial.print("Gib eine Zahl ein: ");
  while (Serial.available() == 0) delay(POLLING_DELAY);
  int input = Serial.parseInt();
  Serial.println(input);

  // signExample(input);
  // rangeExample(input);
  // notExample(input);
  // elseExample(input);
  compoundExample(input);
}

void signExample(int number) {
 if (number > 0) Serial.println("Die Zahl ist positiv.");
 if (number < 0) Serial.println("Die Zahl ist negativ.");
 if (number == 0) Serial.println("Die Zahl ist Null.");
}

void rangeExample(int number) {
  if (number > 10) Serial.println("Das ist eine große Zahl.");
  if (number <= 10) Serial.println("Das ist eine kleine Zahl.");
}

void notExample(int number) {
  if (number != 0) Serial.println("Die Zahl ist nicht Null.");
  if (number == 0) Serial.println("Die Zahl ist tatsächlich Null.");
}

void elseExample(int number) {
  int remainder = number % 2;
  if (remainder == 0) Serial.println("Die Zahl ist gerade.");
  else Serial.println("Die Zahl ist ungerade.");
}

void compoundExample(int number) {
  int remainder = number % 2;
  if (number > 0 && remainder == 0) Serial.println("Das ist eine positive gerade Zahl.");
  if (number < 0 && remainder == 0) Serial.println("Das ist eine negative gerade Zahl.");
  if (remainder == 1) Serial.println("Das ist eine positive ungerade Zahl.");
  if (remainder == -1) Serial.println("Das ist eine negative ungerade Zahl.");
  if (number == 0) Serial.println("Die Zahl ist Null.");
}
