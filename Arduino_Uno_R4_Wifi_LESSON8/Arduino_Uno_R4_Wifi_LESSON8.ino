const int RED_PIN = 8;
const int DIT = 150;
const int DAH = 500;
const int END_WAIT = 1000;

const float MY_PI = 3.14150265;
const char MY_INITIAL = 'C';
const String MY_NAME = "Christoph Jahn";

void setup() {
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  blinkShort();
  blinkShort();
  blinkShort();

  blinkLong();
  blinkLong();
  blinkLong();

  blinkShort();
  blinkShort();
  blinkShort();

  delay(END_WAIT);
}

void blinkShort() {
  digitalWrite(RED_PIN, HIGH); delay(DIT); digitalWrite(RED_PIN, LOW); delay(DIT);
}

void blinkLong() {
  digitalWrite(RED_PIN, HIGH); delay(DAH); digitalWrite(RED_PIN, LOW); delay(DAH); 
}
