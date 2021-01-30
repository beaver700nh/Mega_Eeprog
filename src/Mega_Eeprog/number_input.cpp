#include <Arduino.h>

#include "number_input.hpp"

InputBtns::InputBtns(bool uer, int itv)
{
  m_use_extern_resistors = uer;
  m_interval = itv;
}

void InputBtns::begin()
{
  uint8_t pins[] = {BTN_UP, BTN_DN, BTN_SEL};

  for (uint8_t i = 0; i < 3; ++i) {
    m_buttons[i]->attach(pins[i], (m_use_extern_resistors ? \
                                   INPUT : INPUT_PULLUP));
    m_buttons[i]->interval(m_interval);
  }
}

void InputBtns::update() 
{
  for (uint8_t i = 0; i < 3; ++i) {
    m_buttons[i]->update();
  }
}

uint8_t InputBtns::get_status()
{
  bool a = m_buttons[0]->fell();
  bool b = m_buttons[1]->fell();
  bool c = m_buttons[2]->fell();

  return (a << 2) | (b << 1) | (c);
}

OutputLeds::OutputLeds()
{
  /* empty ctor */;
}

void OutputLeds::begin()
{
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void OutputLeds::show(uint8_t val)
{
  digitalWrite(LED_0, val & 0x01);
  digitalWrite(LED_1, val & 0x02);
  digitalWrite(LED_2, val & 0x04);
  digitalWrite(LED_3, val & 0x08);
}
