#include <Arduino.h>
#include "state_machine.h"

// defines
#define LED_RED_PIN PA7
#define LED_ORANGE_PIN PA6
#define LED_GREEN_PIN PA5

#define BTN_1_PIN PC7
#define BTN_2_PIN PA9
#define BTN_3_PIN PA8
#define BTN_4_PIN PB10



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
