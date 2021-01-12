#include "Constants.h"

void readKeys(boolean &keys, int rowPins[], int colPins[]) { //Updates key states in the keys array
  for (int i = 0; i < COLUMNS; i++) {
    digitalWrite(colPins[i], LOW);
    for (int j = 0; j < ROWS; j++) {
      keys[j][i] = digitalRead(rowPins[j]);
    }
    digitalWrite(colPins[i], HIGH);
  }
}
