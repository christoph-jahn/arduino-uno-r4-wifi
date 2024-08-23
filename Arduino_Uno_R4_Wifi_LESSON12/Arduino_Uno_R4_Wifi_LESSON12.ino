/**
 * Schaltplan mit Potentiometer:
 *   .---------.
 *   |         |GND    ___ 
 *   | Arduino |------|___|----o----.
 *   | Uno R4  |        A      |    |
 *   | Wifi    |A2      |      |    |
 *   |         |--------'      |    |
 *   |         |               |    |
 *   |         |5V             |    |
 *   |         |---------------'    |
 *   |         |                    |
 *   |         |~11  //     ___     |
 *   |         |----->|----|___|----'
 *   '---------'             1k
 *
 * Anmerkung: 
 *   Sobald die LED angeschlossen ist, schwankt der ausgelesene Potentiometerwert +/- 20.
 *   Mit einer Abtastrate von ca. 10x / Sekunde, keine Schwankungen zu beobachten.
 */

const int ANALOG_POTENTIOMETER_PIN = A2;
const int LED_PWM_PIN = 11;
const int MAX_POTENTIOMETER = 1023;
const int SERIAL_BAUD_RATE = 9600;
const int TOLERANCE = 1;
const int POLLING_TIME = 100;

int measurement;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(ANALOG_POTENTIOMETER_PIN, INPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
}

void loop() {
  delay(POLLING_TIME);
  if (!updateMeasurement()) return;

  float voltage = 5.0 / 1023.0 * measurement;
  Serial.print("Messung an PIN " + String(ANALOG_POTENTIOMETER_PIN) + " ist " + String(measurement) + ". ");
  Serial.print("Das entspricht " + String(voltage) + "V. ");

  int brightness = (int) (8.0 * measurement / MAX_POTENTIOMETER);
  analogWrite(LED_PWM_PIN, 1 << brightness);
  Serial.println("Helligkeit der LED am PWM PIN " + String(LED_PWM_PIN) + " ist " + String(brightness) + ". ");
}

bool updateMeasurement() {
  int currentMeasurement = analogRead(ANALOG_POTENTIOMETER_PIN);
  bool inputHasChanged = abs(currentMeasurement - measurement) > TOLERANCE
    || (currentMeasurement < measurement && currentMeasurement <= TOLERANCE)
    || (currentMeasurement > measurement && currentMeasurement >= MAX_POTENTIOMETER - TOLERANCE);
  if (inputHasChanged) measurement = currentMeasurement; 
  return inputHasChanged;
}
