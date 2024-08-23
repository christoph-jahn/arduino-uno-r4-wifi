const int SERIAL_BAUD_RATE = 9600;
const int SERIAL_PRINT_DELAY = 1000;
const int LED_PIN = 10;

const String COUNTER_PRINT_MESSAGE = "The counter is: ";
int counter = 1;

float radius = 2;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //counterExample();
  //sumExample();
  //piExample();
  blinkingLedAndPrintingToSerialMonitor();
}

void counterExample() {
  Serial.print(COUNTER_PRINT_MESSAGE);
  Serial.println(counter);
  counter++;
  delay(SERIAL_PRINT_DELAY);
}

void sumExample() {
  int x = 3;
  int y = 7;
  int z = 10;
  Serial.println(String(x) + " + " + String(y) + " = " + String(z));
  delay(SERIAL_PRINT_DELAY);
}

void piExample() {
  const float MY_PI = 3.14;
  float area = MY_PI * radius * radius;
  Serial.println("A circle of radius " + String(radius) + " has an area of " + String(area) + ".");
  radius = radius + 0.1;
  delay(SERIAL_PRINT_DELAY);
}

void blinkingLedAndPrintingToSerialMonitor() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED an PIN " + String(LED_PIN) + " an.");
  delay(SERIAL_PRINT_DELAY);

  digitalWrite(LED_PIN, LOW);
  Serial.println("LED an PIN "+ String(LED_PIN) + " aus.");
  delay(SERIAL_PRINT_DELAY);
}
