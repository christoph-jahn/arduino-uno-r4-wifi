/**
 * Schaltplan mit Potentiometer:
 *   .---------.
 *   |         |GND    ___ 
 *   | Arduino |------|___|---.
 *   | Uno R4  |        A     |
 *   | Wifi    |A2      |     |
 *   |         |--------'     |
 *   |         |              |
 *   |         |5V            |
 *   |         |--------------'
 *   '---------'
 *
 */

const int ANALOG_POTENTIOMETER_PIN = A2;
const int SERIAL_BAUD_RATE = 9600;
const int WAIT_TIME = 1000;

int measurement; 

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(ANALOG_POTENTIOMETER_PIN, INPUT);
}

void loop() {
  int currentMeasurement = analogRead(ANALOG_POTENTIOMETER_PIN);
  if (abs(currentMeasurement - measurement) <= 1) return; else measurement = currentMeasurement;

  float voltage = 5.0 / 1023.0 * measurement;
  Serial.print("Messung an PIN " + String(ANALOG_POTENTIOMETER_PIN) + " ist " + String(measurement) + ". ");
  Serial.println("Das entspricht " + String(voltage) + "V.");
  delay(WAIT_TIME);
}
