const int RED_LED_PIN = 8;
const int RED_DELAY = 500;
const int RED_REPETITIONS = 10;

const int GREEN_LED_PIN = 7;
const int GREEN_DELAY = 150;
const int GREEN_REPETITIONS = 5;

const int END_WAIT = 1000;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  blinkLED(GREEN_LED_PIN, GREEN_REPETITIONS, GREEN_DELAY);
  blinkLED(RED_LED_PIN, RED_REPETITIONS, RED_DELAY);
  delay(END_WAIT);
}

void blinkLED(int pin, int repetitions, int duration) {
  for (int i=0; i<=repetitions; i++) {
    digitalWrite(pin, HIGH); 
    delay(duration); 
    digitalWrite(pin, LOW); 
    delay(duration);
  }
}

