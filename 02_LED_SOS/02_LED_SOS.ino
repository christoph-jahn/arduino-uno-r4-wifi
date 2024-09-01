void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkShort();
  blinkShort();
  blinkShort();

  blinkLong();
  blinkLong();
  blinkLong();

  blinkShort();
  blinkShort();
  blinkShort();

  delay(1000);
}

void blinkShort() {
  digitalWrite(13, HIGH); delay(100); digitalWrite(13, LOW); delay(100);
}

void blinkLong() {
  digitalWrite(13, HIGH); delay(500); digitalWrite(13, LOW); delay(100); 
}
