#include <SPI.h>
#include <SD.h>

#include "eeprom_controller.hpp"
#include "number_input.hpp"
#include "pin_constants.hpp"

#include "eeprom_addr_bus.hpp"

EepromController ec(EEPROM_WE_B);

void setup()
{
  delay(1000);

  Serial.begin(115200);
  while (!Serial) {
    /* wait for Serial connection */;
  }

  ec.begin();

  Serial.println("Reading EEPROM...");
  for (uint16_t i = 0x0000; i < 0x003F; ++i) {
    uint8_t d = ec.get_eeprom(i);
    Serial.println(d, HEX);
  }

  Serial.println("Writing Test...");
  ec.set_eeprom(0x0000, 0x33);

  Serial.println("Reading Test...");
  Serial.println(ec.get_eeprom(0x0000), HEX);
}

void loop()
{
}
