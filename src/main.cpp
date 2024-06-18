#include <Arduino.h>
#include "state_machine.h"
#include "keypad.h"

// defines
#define LED_RED_LOCKED_PIN PC9
#define LED_GREEN_LOCK_1_PIN PC8
#define LED_GREEN_LOCK_2_PIN PC6
#define LED_GREEN_LOCK_3_PIN PC5

#define BTN_1_PIN PC0
#define BTN_2_PIN PC1
#define BTN_3_PIN PB0
#define BTN_4_PIN PA4

// Pins for the Rotary Encoder
#define RE_PIN_A PB5
#define RE_PIN_B PB3
#define RE_SW PA10

void led_setup();
void button_setup();
void exti_setup();
void check_buttons();
void check_states();
void isr_re();


volatile int32_t counter = 0;

void setup()
{
  led_setup();
  button_setup();
  exti_setup();
  keypad_setup_pins();
  Serial.begin(115200);
}

void loop()
{
  check_buttons();
  check_states();
  Serial.printf("Counter: %d \n", counter);
}

void led_setup()
{
  // Define all leds as output
  pinMode(LED_RED_LOCKED_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_1_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_2_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_3_PIN, OUTPUT);
}

void button_setup()
{
  // Define all buttons as input. PULLUPs are used external
  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
}

void exti_setup()
{
  pinMode(RE_PIN_A, INPUT_PULLUP);
  pinMode(RE_PIN_B, INPUT_PULLUP); 

  attachInterrupt(RE_PIN_A, isr_re, RISING);
}

void isr_re(){
  // TODO : entprellen mit millis()
  if (HIGH == digitalRead(RE_PIN_B))
  {
    // counter clockwise
    counter--;
  }
  else 
  {
    // clockwise
    counter++;
  }
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
    state_machine(OPEN_DOOR);
    state_machine(CLOSE_DOOR);
  }
}

void check_states()
{
  switch (state)
  {
  case SAFE_LOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_1_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_2_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    break;
  case LEVEL_1_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    
    if (char key = get_key())
    {
      Serial.printf("Key: %c \n", key);
    }
    break;
  case LEVEL_2_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    break;
  case LEVEL_3_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_3_PIN, HIGH);
    break;
  default:
    break;
  }
}
