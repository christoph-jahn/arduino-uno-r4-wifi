void setup() {
  for (int i = 9; i <= 13; i++) pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 31; i++) showNumber(i);
}

void showNumber(int number) {
  for (int i = 0; i <= 4; i++) digitalWrite(9 + i, getBitAsPinStatus(number, i));
  delay(200);
}

int getBitAsPinStatus(int number, int bit) {
  if ((number >> bit) % 2 == 0) return LOW;
  return HIGH;
}
