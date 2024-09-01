#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const int SERIAL_BAUD_RATE = 115200;
const int DELAY_TIME = 50;
const int X_MAX = 11;
const int Y_MAX = 7;

int xPos = 3;
int yPos = 2;
int deltaX = 1;
int deltaY = 1;

byte frame[Y_MAX + 1][X_MAX + 1];

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  matrix.begin();
}

void loop() {
  for (int x = 0; x <= X_MAX; x++) { 
    for (int y = 0; y <= Y_MAX; y++) {
      frame[y][x] = 0;
      if (x == xPos && y == yPos) frame[y][x] = 1;
    }
  }

  matrix.renderBitmap(frame, (Y_MAX + 1), (X_MAX + 1));
  if (xPos >= X_MAX || xPos <=0) deltaX = -deltaX;
  if (yPos >= Y_MAX || yPos <=0) deltaY = -deltaY;
  xPos = xPos + deltaX;
  yPos = yPos + deltaY;

  delay(DELAY_TIME);
}
