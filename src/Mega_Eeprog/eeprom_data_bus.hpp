#ifndef EEPROM_DATA_BUS_HPP
#define EEPROM_DATA_BUS_HPP

#include <Arduino.h>

class EepromDataBus
{
  private:
    bool m_mode;
    void set_mode(bool mode);

  public:
    EepromDataBus();
    void begin();
    void set_data(uint8_t data);
    uint8_t get_data();
};

#endif
