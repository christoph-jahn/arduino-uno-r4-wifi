/**
 * In der Arduino IDE:
 *   - öffne den "Seriellen Monitor" (Symbol rechts oben)
 *   - Konfiguration des seriellen Monitors sollte wie folgt sein
 *     - "Kein Zeilenende"
 *     - "115200 Baud"
 *
 * Der "Reset"-Taster auf der Arduino-Platine startet das Programm neu.
 *
 * LED Matrix (8x12, (y,x))
 *
 *      1  2  3  4  5  6  7  8  9 10 11 12
 *   o-------------------------------------> x
 * 1 |  1  .  .  .  .  .  .  .  .  .  .  1
 * 2 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 3 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 4 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 5 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 6 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 7 |  .  .  .  .  .  .  .  .  .  .  .  .
 * 8 |  1  .  .  .  .  .  .  .  .  .  .  1
 *   |
 *   v
 *   y
 * =>  byte frame[Y_MAX][X_MAXS] =
 *   = byte frame[8][12]
 *   = {
 *      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
 *      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
 *      ...
 *      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
 *     }
 * => frame[0][0]  = 1, frame[0][11] = 1
 *    frame[7][0]  = 1, frame[7][11] = 1
 *    alle anderen      frame[y][x]  = 0,
 */

#include "Arduino_LED_Matrix.h"

const int SERIAL_BAUD_RATE = 115200;
const int POLLING_TIME = 50;

ArduinoLEDMatrix matrix;

byte frame[8][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int deltaX = 1;
int deltaY = 1;
int xPos = 0;
int yPos = 0;

const int X_MAX = 11;
const int Y_MAX = 7;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  matrix.begin();
}

void loop() {
  frame[yPos][xPos] = 0;

  xPos = nextPixel(xPos, deltaX, X_MAX);
  yPos = nextPixel(yPos, deltaY, Y_MAX);
  frame[yPos][xPos] = 1;

  matrix.renderBitmap(frame, 8, 12);

  delay(POLLING_TIME);
}

int nextPixel(int position, int& delta, int max) {
  if (position < -delta || position > max - delta) delta = -delta;
  return position + delta;
}
