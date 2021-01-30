#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <Arduino.h>

#include "number_input.hpp"

class Interface
{
  public:
    Interface();

    void begin();

    void info(char *msg1, uint8_t msg2);
    bool get_bool(char *msg1, uint8_t msg2);
    uint8_t get_int(char *msg1, uint8_t msg2);

    void set_leds(uint8_t val);
    void message(char *msg);

  private:
    InputBtns  m_in;
    OutputLeds m_out;
};

#endif
