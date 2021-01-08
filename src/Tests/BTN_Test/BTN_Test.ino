#include "pin_constants.hpp"

void setup()
{
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  pinMode(BTN_UP,  INPUT_PULLUP);
  pinMode(BTN_DN,  INPUT_PULLUP);
  pinMode(BTN_SEL, INPUT_PULLUP);
}

void loop()
{
  digitalWrite(LED_0, digitalRead(BTN_DN));
  digitalWrite(LED_1, digitalRead(BTN_SEL));
  digitalWrite(LED_2, digitalRead(BTN_UP));
}
