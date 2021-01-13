#pragma once
#include "Keypad_constants.h"

void printKeys(boolean* keys) { //For debugging, prints key status (pushed or not) to Serial console. Make sure to uncomment the Serial.begin line at the top of setup if you use this
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      Serial.print(keys[i * COLUMNS + j]);
      if (j == COLUMNS - 1) {
        Serial.println();
      } else {
        Serial.print(" | ");
      }
    }
  }
}

void writeColors(Adafruit_NeoPixel& backlight, uint32_t* colors) { //Writes colors to pixels from the colors array
  int x = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      backlight.setPixelColor(x, colors[i * COLUMNS + j]);
      x++;
    }
  }
  backlight.show();
}

void writeAll(int green, int red, int blue, int white, uint32_t* colors) { //Writes an RGBW value to every slot in the light array
  for (int i = 0;  i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      colors[i * COLUMNS + j] = Adafruit_NeoPixel::Color(green, red, blue, white);
    }
  }
}

void pressedColors(uint32_t* colors, boolean* keys) { //Demo lighting function that sets all pressed keys to rainbow
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (keys[i * COLUMNS + j]) {
        colors[i * COLUMNS + j] = Adafruit_NeoPixel::Color(255, 0, 255, 0);
      } else {
        colors[i * COLUMNS + j] = Adafruit_NeoPixel::Color(0, 255, 255, 0);
      }
    }
  }
}

void readKeys(boolean* keys) { //Updates key states in the keys array
  for (int i = 0; i < COLUMNS; i++) {
    digitalWrite(colPins[i], LOW);
    for (int j = 0; j < ROWS; j++) {
      keys[j * COLUMNS + i] = !digitalRead(rowPins[j]);
    }
    digitalWrite(colPins[i], HIGH);
  }
}

void booleanKeyboard(boolean logic, char key) {
  if (logic) {
    Keyboard.press(key);
  } else {
    Keyboard.release(key);
  }
}

void updateKeys(boolean* keys) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      booleanKeyboard(keys[i * COLUMNS + j], keyAssign[i * COLUMNS + j]);
    }
  }
}
