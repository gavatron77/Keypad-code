#include <Adafruit_NeoPixel.h>

//Config values:
#define ROWS 3
#define COLUMNS 4

int rainR = 000;
int rainG = 255;
int rainB = 255;

int inc = 25;

String rainMode = "gd";

int r = ROWS;
int c = COLUMNS;
double dim = 0.5; //Strip brightness
boolean keys[ROWS][COLUMNS];
int ledloc[ROWS][COLUMNS];
int ledCount = sizeof(keys);
int counter = 0;

int rowPins[ROWS] = {
  7, 8, 9
};

int colPins[COLUMNS] = {
  A0, A1, A2, A3
};

int colors[ROWS][COLUMNS][4]; //LED colors are GRBW, for RGB set the third dimension to 3

Adafruit_NeoPixel backlight(ledCount, A7, NEO_GRBW + NEO_KHZ800);

void setup() {
  backlight.begin();
  Serial.begin(9600);
  delay(5000);
  Serial.println("test");
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
  printKeys();
  counter++;
  if (counter == 20) {
    pressedColors();
    writeColors();
    counter = 0;
    updateRain();
  }
}







void readKeys() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(i + 3, LOW);
    keys[0][i] = digitalRead(0);
    keys[1][i] = digitalRead(1);
    keys[2][i] = digitalRead(2);
    digitalWrite(i + 3, HIGH);
  }
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

void writeColors() { //Writes correct colors to LEDs
  int x = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      backlight.setPixelColor(x, pixelColor(i, j));
      Serial.print("Set pixel ");
      Serial.print(i);
      Serial.print(",  ");
      Serial.print(j);
      Serial.print(" to ");
      Serial.println(pixelColor(i, j));
      x++;
    }
  }
  backlight.show();
}

void writeAll(int green, int red, int blue, int white) {
  Serial.println(colors[0][0][0]);
  Serial.println(colors[0][0][1]);
  Serial.println(colors[0][0][2]);
  Serial.println(colors[0][0][3]);
  for (int i = 0;  i < r; i++) {
    for (int j = 0; j < c; j++) {
      colors[i][j][0] = green;
      colors[i][j][1] = red;
      colors[i][j][2] = blue;
      colors[i][j][3] = white;
    }
  }
  Serial.println(colors[0][0][0]);
  Serial.println(colors[0][0][1]);
  Serial.println(colors[0][0][2]);
  Serial.println(colors[0][0][3]);
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

void pressedColors() {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (keys[i][j]) {
        colors[i][j][0] = 0;
        colors[i][j][1] = 0;
        colors[i][j][2] = 0;
        colors[i][j][3] = 255;
      } else {
        colors[i][j][0] = rainR;
        colors[i][j][1] = rainG;
        colors[i][j][2] = rainB;
        colors[i][j][3] = 0;
      }
    }
  }
}

uint32_t pixelColor(int i, int j) { //Basically just the strip.Color function from the Adafruit Neopixel library, just for the colors array
  return ((uint32_t)colors[i][j][3] << 24) | ((uint32_t)colors[i][j][0] << 16) | ((uint32_t)colors[i][j][1] <<  8) | colors[i][j][2];
}

void updateRain() {
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
