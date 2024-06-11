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

// defines
#define LED_RED_PIN PA7
#define LED_ORANGE_PIN PA6
#define LED_GREEN_PIN PA5

#define BTN_1_PIN PC7
#define BTN_2_PIN PA9
#define BTN_3_PIN PA8
#define BTN_4_PIN PB10

// globale Variablen
State_t state = SAFE_LOCKED;

void setup_btn_and_led();
void check_buttons();
void check_states();

void setup()
{
  // put your setup code here, to run once:
  setup_btn_and_led();
}

void loop()
{
  // put your main code here, to run repeatedly:
  check_buttons();
  check_states();
}

void setup_btn_and_led()
{
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_ORANGE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
}

void check_buttons()
{
  if (LOW == digitalRead(BTN_1_PIN))
  {
    state_machine(INPUT_1_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_2_PIN))
  {
    state_machine(INPUT_2_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_3_PIN))
  {
    state_machine(INPUT_3_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_4_PIN))
  {
    state_machine(INPUT_REFUSED);
  }
}

void check_states(){
  switch (state)
  {
  case SAFE_LOCKED:
    digitalWrite(LED_RED_PIN,HIGH);
    digitalWrite(LED_ORANGE_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    break;
  case LEVEL_1_UNLOCKED:
    digitalWrite(LED_RED_PIN,LOW);
    digitalWrite(LED_ORANGE_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    break;
  case LEVEL_2_UNLOCKED:
    digitalWrite(LED_RED_PIN,LOW);
    digitalWrite(LED_ORANGE_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    break;
  default:
    break;
  }
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