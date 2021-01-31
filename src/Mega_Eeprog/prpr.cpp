#include <Arduino.h>

#include "prpr.hpp"

void prpr_data(uint8_t data[0xFF])
{
  Serial.println();

  Serial.println("   | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
  Serial.println("---+------------------------------------------------");

  for (uint16_t line = 0x0000; line < 0x0100; line += 0x0010)
  {
    char row_label[10];
    sprintf(row_label, "%02X |", line);
    Serial.print(row_label);

    for (uint8_t offset = 0x00; offset < 0x10; ++offset)
    {
      char this_byte[4];
      sprintf(this_byte, " %02x", data[line + offset]);
      Serial.print(this_byte);
    }

    Serial.println();
  }

  Serial.println();
}
