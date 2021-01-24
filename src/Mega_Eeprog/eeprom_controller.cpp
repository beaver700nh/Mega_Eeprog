#include <Arduino.h>

#include "eeprom_controller.hpp"

EepromController::EepromController(uint8_t eeprom_we)
{
  m_eeprom_we = eeprom_we;
}

void EepromController::begin()
{
  m_eab.begin();
  m_edb.begin();

  pinMode(m_eeprom_we, OUTPUT);
  digitalWrite(m_eeprom_we, HIGH);
}

void EepromController::set_eeprom(uint16_t addr, uint8_t data)
{
  m_eab.set_addr(addr, false);
  m_edb.set_data(data);

  digitalWrite(m_eeprom_we, LOW);
  delayMicroseconds(10);
  digitalWrite(m_eeprom_we, HIGH);
  delay(10);
}

uint8_t EepromController::get_eeprom(uint16_t addr)
{
  m_eab.set_addr(addr, true);
  delayMicroseconds(10);
  uint8_t data = m_edb.get_data();
  delayMicroseconds(1);
  return data;
}
