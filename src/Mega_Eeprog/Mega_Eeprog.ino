#include <SPI.h>
#include <SD.h>
#include "eeprom_controller.hpp"
#include "number_input.hpp"
#include "pin_constants.hpp"

//EepromController ec(EEPROM_WE_C);

InputBtns btns(false, 5);
OutputLeds leds;

void setup()
{
  Serial.begin(57600);

  btns.begin();
  leds.begin();
}

void loop()
{
  btns.update();

  if (btns.available()) {
    Serial.println(F("Available!"));

    uint8_t val = btns.get_val();
    Serial.print(F("Value: "));
    Serial.println(val, DEC);
    leds.show(val);
  }

  if (btns.selected()) {
    Serial.println(F("Selected!"));

    leds.show(0x0F);
    delay(1000);
    leds.show(0x00);
  }
}
