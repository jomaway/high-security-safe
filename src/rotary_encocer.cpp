#include "rotary_encoder.h"
#include "Arduino.h"

typedef enum  {
    NONE = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = -1,
} RotationDirection_t;

uint8_t encoder_pinA = 0;
uint8_t encoder_pinB = 0;

volatile int32_t counter = 0;
volatile uint8_t prevState = 0;  // Store previous state (00, 01, 10, 11)

// State table for transitions
RotationDirection_t lookupTable[4][4] = {
  // Previous states: 00, 01, 10, 11
  {NONE,  CLOCKWISE, COUNTERCLOCKWISE,  NONE},   // Current state is 00
  {COUNTERCLOCKWISE, NONE,  NONE,  CLOCKWISE},   // Current state is 01
  {CLOCKWISE,  NONE,  NONE, COUNTERCLOCKWISE},   // Current state is 10
  {NONE, COUNTERCLOCKWISE,  CLOCKWISE,  NONE}    // Current state is 11
};

void isr_re(void);

void setup_encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW)
{
    encoder_pinA = pinA;
    encoder_pinB = pinB;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    // attachInterrupt(pinA, isr_re, RISING); // Detect high->low and low->high edge
    attachInterrupt(pinA, isr_re, CHANGE);
    attachInterrupt(pinB, isr_re, CHANGE);
}
/// @brief get the current state of the encoders counter.
/// @return the current counter value.
int32_t get_encoder_state()
{
    return counter;
}

/// @brief set the encoder state to a new value.
/// @param value an int32_t value
void set_encoder_state(int32_t value)
{
    counter = value;
}


void isr_re()
{
    // Read current state of Channel A and B
    bool state_pinA = digitalRead(encoder_pinA);
    bool state_pinB = digitalRead(encoder_pinB);

    // Combine the two channels into a 2-bit value (00, 01,10,11)
    uint8_t state = (state_pinA << 1) | state_pinB;

    RotationDirection_t direction = lookupTable[prevState][state];

    if (CLOCKWISE == direction){
        counter--;
    } else if (COUNTERCLOCKWISE == direction){
        counter++;
    }

    prevState = state;
}