#ifndef SHIFT_REGISTER_HPP
#define SHIFT_REGISTER_HPP

#include <Arduino.h>

class ShiftRegister
{
  private:
    uint8_t m_cs;
    uint8_t m_bit_order;

  public:
    ShiftRegister(uint8_t cs, uint8_t bit_order);
    void shift(uint16_t data);
};

#endif
