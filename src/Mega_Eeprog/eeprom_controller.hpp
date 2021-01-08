#ifndef EEPROM_CONTROLLER_HPP
#define EEPROM_CONTROLLER_HPP

#include <Arduino.h>

#include "eeprom_addr_bus.hpp"
#include "eeprom_data_bus.hpp"

class EepromController
{
  private:
    EepromAddrBus m_eab;
    EepromDataBus m_edb;

    uint8_t m_eeprom_we;

  public:
    EepromController(uint8_t eeprom_we);
    void set_eeprom(uint16_t addr, uint8_t data);
    uint8_t get_eeprom(uint16_t addr);
};

#endif
