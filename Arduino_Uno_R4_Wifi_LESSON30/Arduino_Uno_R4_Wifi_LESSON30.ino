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

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
 
const int SERIAL_BAUD_RATE = 115200;
const int DELAY_TIME = 250;
int xPos = 3;
int yPos = 2;
int deltaX = 1;
int deltaY = 1;
 
const int DOWN_BUTTON_PIN = 2;
const int UP_BUTTON_PIN = 3;

int myRow = 4;
int downButtonValue;
int upButtonValue;
int rowInc = 1;
int counter = 0;

int column;
int row;
 
byte frame[8][12];
 
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  matrix.begin();
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  downButtonValue = digitalRead(DOWN_BUTTON_PIN);
  upButtonValue = digitalRead(UP_BUTTON_PIN);

  if (downButtonValue == 0) myRow = myRow + rowInc;
  if (upButtonValue == 0) myRow = myRow - rowInc;

  if (counter % 2 == 0) {
    for (column = 0; column <= 11; column = column + 1) {
      for (row = 0; row <= 7; row = row + 1) {
        frame[row][column]=0;
        if (column == xPos && row == yPos) frame[row][column] = 1;
        if (column == 0 && row == myRow) frame[row][column] = 1;
      }
    }

    matrix.renderBitmap(frame,8,12);
    if (xPos >= 11 || xPos <= 0) deltaX = -deltaX;
    if (yPos >= 7 || yPos <= 0) deltaY = -deltaY;

    if (xPos == 0 && yPos != myRow) {
      Serial.println("Game Over, Player 1");
      delay(5000);
    }

    xPos = xPos + deltaX;
    yPos = yPos + deltaY;
  }
  counter++;

  delay(DELAY_TIME);
}
