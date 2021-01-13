#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>

#include "Keypad_constants.h"
#include "Keypad_functions.h"

boolean keys[ROWS * COLUMNS];
int ledloc[ROWS * COLUMNS];
boolean written = false;

uint32_t colors[ROWS * COLUMNS]; //LED colors are GRBW, for RGB set the third dimension to 3

Adafruit_NeoPixel backlight(ROWS * COLUMNS, 7, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  backlight.begin();
  Keyboard.begin();

  backlight.setBrightness(255);

  pinMode(H1, INPUT_PULLUP);
  pinMode(H2, INPUT_PULLUP);
  pinMode(H3, INPUT_PULLUP);

  pinMode(V1, OUTPUT);
  pinMode(V2, OUTPUT);
  pinMode(V3, OUTPUT);
  pinMode(V4, OUTPUT);

  digitalWrite(V1, HIGH);
  digitalWrite(V2, HIGH);
  digitalWrite(V3, HIGH);
  digitalWrite(V4, HIGH);

  writeAll(0, 0, 0, 255, colors);
  writeColors(backlight, colors);
}

void loop() {
  readKeys(keys);
  updateKeys(keys);

  pressedColors(colors, keys);
  writeColors(backlight, colors);
}
