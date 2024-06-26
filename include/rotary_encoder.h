#ifndef RE_H
#define RE_H

#include <inttypes.h>

void setup_encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW);
int get_counter();
void set_counter(int32_t value);

#endif // RE_H