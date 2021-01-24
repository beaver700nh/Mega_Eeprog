#ifndef SHIFT_REGISTER_HPP
#define SHIFT_REGISTER_HPP

#include <Arduino.h>

class ShiftRegister
{
  private:
    uint8_t m_bit_order;
    bool m_const_oe;

  public:
    ShiftRegister(uint8_t bit_order, bool const_oe);
    void begin();

    void shift(uint16_t data);
    void update();

    void output_on();
    void output_off();
};

#endif
