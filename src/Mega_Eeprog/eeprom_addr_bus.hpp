#ifndef EEPROM_ADDR_BUS_HPP
#define EEPROM_ADDR_BUS_HPP

#include <Arduino.h>

#include "shift_register.hpp"

class EepromAddrBus
{
  private:
    ShiftRegister m_shr;

  public:
    EepromAddrBus();
    void begin();
    void set_addr(uint16_t addr, bool oe);
};

#endif
