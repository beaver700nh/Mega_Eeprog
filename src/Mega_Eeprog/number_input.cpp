#include <Arduino.h>

#include "number_input.hpp"

InputBtns::InputBtns(bool uer, int itv) {
  m_use_extern_resistors = uer;
  m_interval = itv;
}

void InputBtns::begin() {
  uint8_t pins[] = {BTN_UP, BTN_DN, BTN_SEL};

  for (uint8_t i = 0; i < 3; ++i) {
    m_buttons[i]->attach(pins[i], (m_use_extern_resistors ? \
                                   INPUT : INPUT_PULLUP));
    m_buttons[i]->interval(m_interval);
  }
}

void InputBtns::update() {
  for (uint8_t i = 0; i < 3; ++i) {
    m_buttons[i]->update();
  }

  if (m_buttons[0]->fell()) {
    ++m_val;
    m_available = true;
  }
  else if (m_buttons[1]->fell()) {
    --m_val;
    m_available = true;
  }

  if (m_buttons[2]->fell()) {
    m_selected = true;
  }
}

bool InputBtns::available() {
  return m_available;
}

bool InputBtns::selected() {
  if (m_selected) {
    m_selected = false;
    return true;
  }
  else {
    return false;
  }
}

int8_t InputBtns::get_val() {
  if (m_available) {
    m_available = false;
    return m_val;
  }
  else {
    return -1;
  }
}

OutputLeds::OutputLeds() {
  /* empty ctor */;
}

void OutputLeds::begin() {
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void OutputLeds::show(uint8_t val) {
  digitalWrite(LED_0, val & 0x01);
  digitalWrite(LED_1, val & 0x02);
  digitalWrite(LED_2, val & 0x04);
  digitalWrite(LED_3, val & 0x08);
}
