#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>

#define ROWS 3
#define COLUMNS 4

char keyAssign[ROWS][COLUMNS] {
  {KEY_F13, KEY_F14, KEY_F15, KEY_F16},
  {KEY_F17, KEY_F18, KEY_F19, KEY_F20},
  {KEY_F21, KEY_F22, KEY_F23, KEY_F24}
};

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

Adafruit_NeoPixel backlight(ledCount, 7, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  backlight.begin();
  Keyboard.begin();
  backlight.setBrightness(255);
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
  readKeys();
  updateKeys();

  counter++;
  if (counter == 10) {
    pressedColors();
    writeColors();
    counter = 0;
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
        colors[i][j][0] = 255;
        colors[i][j][1] = 0;
        colors[i][j][2] = 255;
        colors[i][j][3] = 0;
      } else {
        colors[i][j][0] = 0;
        colors[i][j][1] = 255;
        colors[i][j][2] = 255;
        colors[i][j][3] = 0;
      }
    }
  }
}

void readKeys() { //Updates key states in the keys array
  for (int i = 0; i < COLUMNS; i++) {
    digitalWrite(colPins[i], LOW);
    for (int j = 0; j < ROWS; j++) {
      keys[j][i] = !digitalRead(rowPins[j]);
    }
    digitalWrite(colPins[i], HIGH);
  }
}

uint32_t pixelColor(int i, int j) { //Basically just the strip.Color function from the Adafruit Neopixel library, just for the colors array
  return ((uint32_t)colors[i][j][3] << 24) | ((uint32_t)colors[i][j][0] << 16) | ((uint32_t)colors[i][j][1] <<  8) | colors[i][j][2];
}

void updateKeys() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      booleanKeyboard(keys[i][j], keyAssign[i][j]);
    }
  }
}

void booleanKeyboard(boolean logic, char key) {
  if (logic) {
    Keyboard.press(key);
  } else {
    Keyboard.release(key);
  }
}
