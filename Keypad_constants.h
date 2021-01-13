#pragma once

#define ROWS 3
#define COLUMNS 4

const uint8_t keyAssign[ROWS * COLUMNS] {
  KEY_F13, KEY_F14, KEY_F15, KEY_F16,
  KEY_F17, KEY_F18, KEY_F19, KEY_F20,
  KEY_F21, KEY_F22, KEY_F23, KEY_F24
};

#define H1 0
#define H2 1
#define H3 2

const int rowPins[ROWS] = {
  H1, H2, H3
};

#define V1 3
#define V2 4
#define V3 5
#define V4 6

const int colPins[COLUMNS] = {
  V1, V2, V3, V4
};
