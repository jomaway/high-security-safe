#include "keypad.h"
uint64_t last_reading_time = 0;
uint8_t last_key = 0;

void keypad_setup_pins()
{
    // init all col pins as OUTPUT and set to HIGH.
    for (uint8_t c = 0; c < COLS_NUM; c++)
    {
        pinMode(col_pins[c], OUTPUT);
        digitalWrite(col_pins[c], HIGH);
    }

    // init all row pins as INPUT with a internal PULLUP
    for (uint8_t r = 0; r < ROWS_NUM; r++)
    {
        pinMode(row_pins[r], INPUT_PULLUP);
    }
}

char get_key()
{
    char key = NO_KEY;
    if ((millis() - last_reading_time) > DEBOUNCE_TIME)
    {
        uint8_t current_key = read_keys();
        if (last_key != current_key)
        {
            key = map_key(current_key);
            last_key = current_key;
        }
        last_reading_time = millis();
    }
    
    return key;
}

// returns a value between 0 and 16
uint8_t read_keys()
{
    uint8_t key = 0;
    for (uint8_t c = 0; c < COLS_NUM; c++)
    {
        digitalWrite(col_pins[c], LOW);

        for (uint8_t r = 0; r < ROWS_NUM; r++)
        {
            if (LOW == digitalRead(row_pins[r]))
            {
                key = (c + 1) + (4 * r);
            }
        }

        digitalWrite(col_pins[c], HIGH);
    }
    return key;
}

char map_key(uint8_t key)
{
    if(key >= 1 and key <=16){
        key--;  // to get a range from 0 to 15
        uint8_t row = key / 4; 
        uint8_t col = key % 4; // Modulo operator gibt REST zurück bei Division durch 4.
        return keymap[row][col];
    }
    return NO_KEY;
}
