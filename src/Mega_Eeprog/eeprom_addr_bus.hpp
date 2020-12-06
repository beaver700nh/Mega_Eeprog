#ifndef EEPROM_ADDR_BUS_HPP
#define EEPROM_ADDR_BUS_HPP

#include <Arduino.h>

#include "shift_register.hpp"

class EepromAddrBus
{
  private:
    ShiftRegister m_shr;

  public:
    EepromAddrBus(uint8_t shr_cs);
    void set_address(uint16_t addr, bool oe);
}

#endif
