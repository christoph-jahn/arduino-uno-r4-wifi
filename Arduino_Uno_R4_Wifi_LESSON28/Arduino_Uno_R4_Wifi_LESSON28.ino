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

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  matrix.begin();
}

void loop() {
  //exampleSinglePixel();
  //exampleCorners();
  //exampleThirdRow();
  //exampleEightColumn();
  //exampleAllOn();
  //exampleAnimateByColumn();
  //exampleAnimateByPixel();
  exampleFlickering();

  delay(POLLING_TIME);
}

void exampleSinglePixel() {
  frame[2][4] = 1;
  matrix.renderBitmap(frame, 8, 12);
}

void exampleCorners() {
  frame[0][0] = 1;
  frame[0][11] = 1;
  frame[7][0] = 1;
  frame[7][11] = 1;
  matrix.renderBitmap(frame, 8, 12);
}

void exampleThirdRow() {
  for (int column = 0; column < 12; column++) frame[2][column] = 1;
  matrix.renderBitmap(frame, 8, 12);
}

void exampleEightColumn() {
  for (int row = 0; row < 8; row++) frame[row][7] = 1;
  matrix.renderBitmap(frame, 8, 12);
}

void exampleAllOn() {
  for (int column = 0; column < 11; column++) {
    for (int row = 0; row < 8; row++) frame[row][column] = 1;
  }
  matrix.renderBitmap(frame, 8, 12);
}

void exampleAnimateByColumn() {
  for (int column = 0; column < 11; column++) {
    for (int row = 0; row < 8; row++) frame[row][column] = 1;
    matrix.renderBitmap(frame, 8, 12);
    delay(250);
  }
}

void exampleAnimateByPixel() {
  for (int column = 0; column < 11; column++) {
    for (int row = 0; row < 8; row++) {
      frame[row][column] = 1;
      delay(25);
      matrix.renderBitmap(frame, 8, 12);
    }
  }
}

void exampleFlickering() {
  for (int column = 0; column < 11; column++) {
    for (int row = 0; row < 8; row++) {
      frame[row][column] = !frame[row][column];
    }
    delay(25);
    matrix.renderBitmap(frame, 8, 12);
  }
}
