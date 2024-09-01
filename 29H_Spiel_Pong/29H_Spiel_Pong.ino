/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "115200 Baud"
 *
 * Der "Reset"-Taster auf der Arduino-Platine startet das Programm neu.
 *
 * Schaltplan:
 *   .-------------.
 *   | Arduino Uno |
 *   | R4 Wifi     |
 *   |           _/|                  Grün
 *   |          |3 o---------------o |
 *   |          |_/|        Rot      |=|
 *   |          |2 o------o |      o |
 *   |          |_/|        |=|    |
 *   |             |      o |      |
 *   |             |GND   |        |
 *   |             |------o--------'
 *   '-------------'
 *
 * Beachte, dass ArduinoGraphics.h (v1.1.2) vor Arduino_LED_Matrix.h inkludiert werden muss!
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

const int RED_BUTTON_PIN = 2;
const int GREEN_BUTTON_PIN = 3;

const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 10;

const int X_MAX = 12;
const int Y_MAX = 8;

const int BALL_SPEED = 20;

int redButtonValue = 1;
int greenButtonValue = 1;

ArduinoLEDMatrix matrix;

byte frame[Y_MAX][X_MAX];

int deltaX;
int deltaY;
int ballX;
int ballY;

int playerY;
int hits;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
  matrix.begin();
  initializeScreen();
}

void loop() {
  for (int i = 0; i < BALL_SPEED; i++) {
    updatePlayer();
    matrix.renderBitmap(frame, Y_MAX, X_MAX);
    delay(POLLING_TIME);
  }
  moveBall();

  if (ballX != 0) return;

  if (ballY == playerY) {
    moveBall();
    frame[playerY][0] = 1;
    hits++;
  } else gameEnd();
}

void initializeScreen() {
  hits = 0;
  deltaX = 1;
  deltaY = 1;
  ballX = 3;
  ballY = 3;
  playerY = 3;

  for (int x = 0; x < X_MAX; x++) {
    for (int y = 0; y < Y_MAX; y++) {
      frame[y][x] = 0;
    }
  }

  frame[playerY][0] = 1;
  frame[ballY][ballX] = 1;
  matrix.renderBitmap(frame, Y_MAX, X_MAX);
}

void updatePlayer() {
  bool moveUp = isButtonPushed(GREEN_BUTTON_PIN, greenButtonValue);
  bool moveDown = isButtonPushed(RED_BUTTON_PIN, redButtonValue);

  if (moveUp || moveDown) {
    frame[playerY][0] = 0;
    if (moveUp) playerY = max(playerY - 1, 0);
    if (moveDown) playerY = min(playerY + 1, Y_MAX - 1);
    frame[playerY][0] = 1;
  }
}

bool isButtonPushed(int buttonPin, int& oldValue) {
  int newValue = digitalRead(buttonPin);
  bool result = (newValue == 1) && (oldValue != newValue);
  oldValue = newValue;
  return result;
}

void moveBall() {
  frame[ballY][ballX] = 0;
  ballX = nextBallPosition(ballX, deltaX, X_MAX - 1);
  ballY = nextBallPosition(ballY, deltaY, Y_MAX - 1);
  frame[ballY][ballX] = 1;
}

int nextBallPosition(int position, int& delta, int max) {
  if (position <= 0 || position >= max) delta = -delta;
  return position + delta;
}

void gameEnd() {
  matrix.renderBitmap(frame, Y_MAX, X_MAX);
  delay(2000);
  showText("Spielende. " + String(hits) + " Punkt" + (hits > 1 ? "e" : "") +". Neues Spiel in");
  for (int i = 3; i > 0; i--) {
    showNumber(i);
    delay(1000);
  }
  initializeScreen();
}

void showText(String text) {
  matrix.beginDraw();
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 255, 0, 0);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

void showNumber(int number) {
  matrix.beginDraw();
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 255, 0, 0);
  matrix.println((number < 10 ? " " : "") +String(number));
  matrix.endText();
  matrix.endDraw();
}