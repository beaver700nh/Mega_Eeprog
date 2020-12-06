#ifndef EEPROM_DATA_BUS_HPP
#define EEPROM_DATA_BUS_HPP

#include <Arduino.h>

class EepromDataBus
{
  private:
    uint8_t m_bit_order;

  public:
    EepromDataBus(uint8_t bit_order);
    void set_data(uint8_t data);
    uint8_t get_data();
}

#endif
