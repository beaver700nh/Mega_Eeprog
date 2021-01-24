#include <Arduino.h>
#include <SPI.h>

#include "shift_register.hpp"
#include "pin_constants.hpp"

ShiftRegister::ShiftRegister(uint8_t bit_order, bool const_oe)
{
  m_bit_order = bit_order;
  m_const_oe = const_oe;
}

void ShiftRegister::begin()
{
  pinMode(SHR_LATCH, OUTPUT);
  digitalWrite(SHR_LATCH, LOW);
  SPI.begin();
}

void ShiftRegister::shift(uint16_t data)
{
  SPI.beginTransaction(SPISettings(20000, m_bit_order, SPI_MODE0));
  SPI.transfer(data);
  SPI.endTransaction();
}

void ShiftRegister::update()
{
  digitalWrite(SHR_LATCH, HIGH);
  delayMicroseconds(1);
  digitalWrite(SHR_LATCH, LOW);
}

void ShiftRegister::output_on()
{
  if (!m_const_oe) {
    digitalWrite(SHR_OE, LOW);
  }
}

void ShiftRegister::output_off()
{
  if (!m_const_oe) {
    digitalWrite(SHR_OE, HIGH);
  }
}
