#include <Arduino.h>

typedef enum
{
  SAFE_LOCKED,
  LEVEL_1_UNLOCKED,
  LEVEL_2_UNLOCKED,
  LEVEL_3_UNLOCKED,
  SAFE_OPEN,
} State_t;

typedef enum
{
  INPUT_1_ACCEPTED,
  INPUT_2_ACCEPTED,
  INPUT_3_ACCEPTED,
  INPUT_REFUSED,
  OPEN_DOOR,
  CLOSE_DOOR,
} Event_t;

void state_machine(Event_t event);

// globale Variablen
State_t state = SAFE_LOCKED;

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:

}

void state_machine(Event_t event)
{
  switch (state)
  {
  case SAFE_LOCKED:
    if (INPUT_1_ACCEPTED == event)
    {
      state = LEVEL_1_UNLOCKED;
    }
    break;
  case LEVEL_1_UNLOCKED:
    if (INPUT_2_ACCEPTED == event)
    {
      state = LEVEL_2_UNLOCKED;
    }
    else if (INPUT_REFUSED == event)
    {
      state = SAFE_LOCKED;
    }
    break;
  case LEVEL_2_UNLOCKED:
    if (INPUT_3_ACCEPTED == event)
    {
      state = LEVEL_3_UNLOCKED;
    }
    else if (INPUT_REFUSED == event)
    {
      state = SAFE_LOCKED;
    }
    break;
  case LEVEL_3_UNLOCKED:
    if (OPEN_DOOR == event)
    {
      state = SAFE_OPEN;
    }
    break;
  case SAFE_OPEN:
    if (CLOSE_DOOR == event)
    {
      state = SAFE_LOCKED;
    }
    break;
  }
}