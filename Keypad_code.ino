#include <Adafruit_NeoPixel.h>

//Config values:
#define ROWS 3
#define COLUMNS 4

int r = ROWS;
int c = COLUMNS;
double dim = 0.5; //When colors are set they are multiplied by this value
boolean keys[ROWS][COLUMNS];
int ledloc[ROWS][COLUMNS];
int ledCount = sizeof(keys);

int rowPins[ROWS] = {
  A0, A1, A2
};

int colPins[COLUMNS] = {
  A3, A4, A5, A6
};

int colPins[COLUMNS];

int colors[ROWS][COLUMNS][4]; //LED colors are GRBW, for RGB set the third dimension to 3

Adafruit_NeoPixel backlight(ledCount, A7, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  int counter = 0;

  for (int i = 0; i < r; i++) { //Sets LED locations
    for (int j = 0; j < c; j++) {
      ledloc[i][j] = counter;
      counter++;
      Serial.println(counter);
    }
  }

  Serial.println();

  printLocs();
  writeColors();
}



void loop() {
  for (int i = 0; i < r; i++) {
    highRow(i);
    for (int j = 0; j < c; j++) {
      if (digitalRead(A0)) {
      }
    }
  }
}









void highRow(int row) { //Sets all rows except selected row to low
  digitalWrite(A0, row == 0);
  digitalWrite(A1, row == 1);
  digitalWrite(A2, row == 2);
}

void printKeys() { //For debugging, prints key status (pushed or not) to Serial console
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      Serial.print(keys[i][j]);
      if (j == c - 1) {
        Serial.println();
      } else {
        Serial.print(" | ");
      }
    }
  }
}

void printLocs() { //For debugging, prints LED number locations to Serial console
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      Serial.print(ledloc[i][j]);
      if (j == c - 1) {
        Serial.println();
      } else {
        Serial.print(" | ");
      }
    }
  }
}

void resetKeys() { //Sets all keys in keys array to unpressed
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      keys[i][j] = false;
    }
  }
}

void a() { //Sets all keys in keys array to unpressed
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      keys[i][j] = false;
    }
  }
}

void writeColors() { //Writes correct colors to LEDs
  int x = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      backlight.setPixelColor(x, pixelColor(i, j));
    }
  }
}

void writeAll(int g, int r, int b, int w) {
  for (int i = 0;  i < r; i++) {
    for (int j = 0; j < c; j++) {
      colors[i][j][0] = g;
      colors[i][j][1] = r;
      colors[i][j][2] = b;
      colors[i][j][3] = w;
    }
  }
}

void constrainColors() {
  for (int i = 0;  i < r; i++) {
    for (int j = 0; j < c; j++) {
      for (int k = 0; k < 3; k++) {
        colors[i][j][k] = constrain(colors[i][j][k], 0, 255);
      }
    }
  }
}

uint32_t pixelColor(int i, int j) { //Basically just the strip.Color function from the Adafruit Neopixel library, just for the colors array
  return ((uint32_t)colors[i][j][3] << 24) | ((uint32_t)colors[i][j][0] << 16) | ((uint32_t)colors[i][j][1] <<  8) | colors[i][j][2];
}
