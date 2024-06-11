#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

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

extern State_t state;

void state_machine(Event_t event);

#endif  // STATE_MACHINE_H