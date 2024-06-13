#ifndef KEYPAD_H
#define KEYPAD_H

#include <inttypes.h>
#include "Arduino.h"

#define ROWS_NUM 4
#define COLS_NUM 4

#define KEYPAD_ROW_1 PA5
#define KEYPAD_ROW_2 PA6
#define KEYPAD_ROW_3 PA7
#define KEYPAD_ROW_4 PB6

#define KEYPAD_COL_1 PC7
#define KEYPAD_COL_2 PA9
#define KEYPAD_COL_3 PA8
#define KEYPAD_COL_4 PB10

#define DEBOUNCE_TIME 10
const char NO_KEY = '\0';

// Define the keymap
const char keymap[ROWS_NUM][COLS_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const int row_pins[ROWS_NUM] = {KEYPAD_ROW_1, KEYPAD_ROW_2, KEYPAD_ROW_3, KEYPAD_ROW_4};
const int col_pins[COLS_NUM] = {KEYPAD_COL_1, KEYPAD_COL_2, KEYPAD_COL_3, KEYPAD_COL_4};

void keypad_setup_pins();
uint8_t read_keys();
char map_key(uint8_t key);
char get_key();

#endif // KEYPAD_H