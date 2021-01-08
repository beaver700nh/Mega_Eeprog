#include <Bounce2.h>
#include "pin_constants.hpp"

bool rw_sig_state = LOW;
uint8_t current_val = 0x00;

Bounce *buttons[] = {
  new Bounce(),
  new Bounce(),
  new Bounce()
};

void write_program_id(uint8_t id);

void setup()
{
  Serial.begin(57600);

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(RW_SIG, OUTPUT);

  uint8_t pins[] = {BTN_UP, BTN_DN, BTN_SEL};

  for (uint8_t i = 0; i < 3; ++i) {
    buttons[i]->attach(pins[i], INPUT_PULLUP);
    buttons[i]->interval(5);
  }
}

void loop()
{
  for (uint8_t i = 0; i < 3; ++i) {
    buttons[i]->update();
  }

  if (buttons[0]->fell()) {
    ++current_val;
  }
  else if (buttons[1]->fell()) {
    --current_val;
  }

  if (buttons[2]->fell()) {
    rw_sig_state = !rw_sig_state;
    digitalWrite(RW_SIG, rw_sig_state);
  }

  Serial.println(current_val, HEX);
  write_program_id(current_val);
}

void write_program_id(uint8_t id) {
  digitalWrite(LED_0, id & 0x01);
  digitalWrite(LED_1, id & 0x02);
  digitalWrite(LED_2, id & 0x04);
  digitalWrite(LED_3, id & 0x08);
}
