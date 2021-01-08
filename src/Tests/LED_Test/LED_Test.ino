#include "pin_constants.hpp"

int foo = LOW;

void setup()
{
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(RW_SIG, OUTPUT);
}

void loop()
{
  digitalWrite(RW_SIG, foo);

  foo = (foo == LOW ? HIGH : LOW);

  digitalWrite(LED_0, HIGH);
  delay(500);
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, HIGH);
  delay(500);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(500);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, HIGH);
  delay(500);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_2, HIGH);
  delay(500);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_1, HIGH);
  delay(500);
  digitalWrite(LED_1, LOW);
}
