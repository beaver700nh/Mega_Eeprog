#include <SPI.h>
#include <SD.h>

#include "eeprom_controller.hpp"
#include "number_input.hpp"
#include "pin_constants.hpp"

#include "interface.hpp"

#define ACTION_WRITE  0x08
#define ACTION_READ   0x04
#define ACTION_VECTOR 0x02

//EepromController ec(EEPROM_WE_B);

uint8_t file, slot, vector;

uint8_t get_value(char *prompt1, uint8_t prompt2);
char *action_str_repr(uint8_t action);

Interface itf;

void setup()
{
  delay(1000);

  itf.begin();
  itf.info("Welcome to Mega Eeprog by Minh Le!", 0xFF);
}

void loop()
{
  uint8_t action;

  while (true)
  {
    action = get_value("Please select an action.", 0x08);
  
    if (action == ACTION_WRITE)
    {
      file = get_value("Select file to write.", 0x0C);
      slot = get_value("Select slot to write to.", 0x0C);
      break;
    }
    else if (action == ACTION_READ)
    {
      slot = get_value("Select slot to read from.", 0x0A);
      break;
    }
    else if (action == ACTION_VECTOR)
    {
      vector = get_value("Select vector to set.", 0x09);
      slot = get_value("Select slot to jump to.", 0x09);
      break;
    }
    else
    {
      itf.message("Invalid action.");
      itf.set_leds(0x00);
    }
  }

  Serial.print("Continue with action? ");

  if (!itf.get_bool(action_str_repr(action), action))
  {
    itf.message("Canceled.");
    itf.set_leds(0x06);
    return;
  }

  Serial.println("Operating...");
}

uint8_t get_value(char *prompt1, uint8_t prompt2)
{
  while (true)
  {
    uint8_t res = itf.get_int(prompt1, prompt2);

    if (itf.get_bool("Are you sure?", 0xFF))
    {
      itf.message("Ok.");
      itf.set_leds(0x00);
      return res;
    }
  }
}

char *action_str_repr(uint8_t action)
{
  if (action == ACTION_WRITE)
  {
    return "<write>";
  }
  else if (action == ACTION_READ)
  {
    return "<read>";
  }
  else if (action == ACTION_VECTOR)
  {
    return "<vector-set>";
  }
}
