#include <Arduino.h>

#include "eeprom_addr_bus.hpp"
#include "shift_register.hpp"

EepromAddrBus::EepromAddrBus() : m_shr(MSBFIRST, true)
{
  /* empty ctor */;
}

void EepromAddrBus::begin()
{
  m_shr.begin();
}

void EepromAddrBus::set_addr(uint16_t addr, bool oe) 
{
  m_shr.shift((addr >> 8) | (oe ? 0x00 : 0x80));
  m_shr.shift(addr & 0xff);
  m_shr.update();
}
