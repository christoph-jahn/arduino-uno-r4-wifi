void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 15; i++) {
    showNumber(i);
    delay(100);
  }
}

void showNumber(int number) {
  digitalWrite(10, getBitAsPinStatus(number, 0));
  digitalWrite(11, getBitAsPinStatus(number, 1));
  digitalWrite(12, getBitAsPinStatus(number, 2));
  digitalWrite(13, getBitAsPinStatus(number, 3));
}

int getBitAsPinStatus(int number, int bit) {
  if ((number >> bit) % 2 == 0) {
    return LOW;
  }
  return HIGH;
}
