#include "rotary_encoder.h"
#include "Arduino.h"

uint64_t last_re_reading_time = 0;

uint8_t encoder_pinA = 0;
uint8_t encoder_pinB = 0;

volatile int32_t counter = 0;
void isr_re(void);

void setup_encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW)
{
    encoder_pinA = pinA;
    encoder_pinB = pinB;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    attachInterrupt(pinA, isr_re, RISING); // Detect high->low and low->high edge
}

int get_counter()
{
    return counter;
}

void set_counter(int32_t value)
{
    counter = value;
}

void isr_re()
{
    bool state_pinB = digitalRead(encoder_pinB);
    if ((millis() - last_re_reading_time) > 10)
    {
        if (HIGH == state_pinB)
        {
            // counter clockwise
            counter--;
        }
        else
        {
            // clockwise
            counter++;
        }
        last_re_reading_time = millis();
        // Serial.printf("Counter: %d \n", counter % 12);
    }
}