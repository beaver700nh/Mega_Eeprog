#include <Arduino.h>

#include "eeprom_data_bus.hpp"
#include "pin_constants.hpp"

EepromDataBus::EepromDataBus()
{
  m_mode = OUTPUT;
}

void EepromDataBus::begin()
{
  set_mode(m_mode);
}

void EepromDataBus::set_data(uint8_t data)
{
  set_mode(OUTPUT);
  delayMicroseconds(5);
  EEPROM_DATA_OUT = data;
}

uint8_t EepromDataBus::get_data()
{
  set_mode(INPUT);
  delayMicroseconds(5);
  return EEPROM_DATA_IN;
}

void EepromDataBus::set_mode(bool mode)
{
  EEPROM_DATA_DIR = (mode == OUTPUT ? 0xFF : 0x00);
}
