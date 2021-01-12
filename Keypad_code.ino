#include <Adafruit_NeoPixel.h>
#include "Keypad_functions.h"
#include "Constants.h"

int rainR = 000;
int rainG = 255;
int rainB = 255;
String rainMode = "gd";

int inc = 1; //How fast the rainbow updates, higher = faster

double dim = 0.1; //Strip brightness
boolean keys[ROWS][COLUMNS];
int ledloc[ROWS][COLUMNS];
int ledCount = sizeof(keys);
int counter = 0;

int rowPins[ROWS] = {
  0, 1, 2
};

int colPins[COLUMNS] = {
  3, 4, 5, 6
};

int colors[ROWS][COLUMNS][4]; //LED colors are GRBW, for RGB set the third dimension to 3

Adafruit_NeoPixel backlight(ledCount, A7, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  backlight.begin();
  backlight.setBrightness(constrain(dim * 255, 0, 255));
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  writeAll(0, 0, 0, 255);
  writeColors();
}


void loop() {
  readKeys(keys, rowPins, colPins);
  writePresses;
  counter++;
  if (counter == 100) {
    pressedColors();
    writeColors();
    counter = 0;
    updateRain();
  }
}





void printKeys() { //For debugging, prints key status (pushed or not) to Serial console. Make sure to uncomment the Serial.begin line at the top of setup if you use this
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      Serial.print(keys[i][j]);
      if (j == COLUMNS - 1) {
        Serial.println();
      } else {
        Serial.print(" | ");
      }
    }
  }
}

void writeColors() { //Writes colors to pixels from the colors array
  int x = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      backlight.setPixelColor(x, pixelColor(i, j));
      x++;
    }
  }
  backlight.show();
}

void writeAll(int green, int red, int blue, int white) { //Writes an RGBW value to every slot in the light array
  for (int i = 0;  i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      colors[i][j][0] = green;
      colors[i][j][1] = red;
      colors[i][j][2] = blue;
      colors[i][j][3] = white;
    }
  }
}

void pressedColors() { //Demo lighting function that sets all pressed keys to rainbow
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (keys[i][j]) {
        colors[i][j][0] = rainR;
        colors[i][j][1] = rainG;
        colors[i][j][2] = rainB;
        colors[i][j][3] = 0;
      } else {
        colors[i][j][0] = 255 - rainR;
        colors[i][j][1] = 255 - rainG;
        colors[i][j][2] = 255 - rainB;
        colors[i][j][3] = 0;
      }
    }
  }
}

void updateRain() { //Called every few loops, updates the rainbow values
  if (rainMode == "ru") {
    rainR += inc;
  } else if (rainMode == "rd") {
    rainR -= inc;
  } else if (rainMode == "gu") {
    rainG += inc;
  } else if (rainMode == "gd") {
    rainG -= inc;
  } else if (rainMode == "bu") {
    rainB += inc;
  } else if (rainMode == "bd") {
    rainB -= inc;
  }

  rainR = constrain(rainR, 0, 255);
  rainG = constrain(rainG, 0, 255);
  rainB = constrain(rainB, 0, 255);

  if (rainR == 255 && rainG == 255) {
    rainMode = "rd";
  } else if (rainG == 255 && rainB == 255) {
    rainMode = "gd";
  } else if (rainB == 255 && rainR == 255) {
    rainMode = "bd";
  } else if (rainR == 0 && rainG == 0) {
    rainMode = "ru";
  } else if (rainG == 0 && rainB == 0) {
    rainMode = "gu";
  } else if (rainB == 0 && rainR == 0) {
    rainMode = "bu";
  }
}

uint32_t pixelColor(int i, int j) { //Basically just the strip.Color function from the Adafruit Neopixel library, just for the colors array
  return ((uint32_t)colors[i][j][3] << 24) | ((uint32_t)colors[i][j][0] << 16) | ((uint32_t)colors[i][j][1] <<  8) | colors[i][j][2];
}
