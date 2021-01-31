#include <SPI.h>
#include <SD.h>

#include "Mega_Eeprog.hpp"
#include "eeprom_controller.hpp"
#include "pin_constants.hpp"
#include "interface.hpp"

//EepromController ec(EEPROM_WE_B);

uint8_t file, slot, vector;

uint8_t get_value(const char *prompt1, uint8_t prompt2);

bool do_action_write();
bool do_action_read();
bool do_action_vector();

Interface itf;

bool (*func)();

void setup()
{
  delay(1000);

  itf.begin();
  itf.info("Welcome to Mega Eeprog by Minh Le!", 0x0F);
  delay(750);
  itf.set_leds(0x00);
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
      func = do_action_write;
      break;
    }
    else if (action == ACTION_READ)
    {
      slot = get_value("Select slot to read from.", 0x0A);
      func = do_action_read;
      break;
    }
    else if (action == ACTION_VECTOR)
    {
      vector = get_value("Select vector to set.", 0x09);
      slot = get_value("Select slot to jump to.", 0x09);
      func = do_action_vector;
      break;
    }
    else
    {
      itf.info("Invalid action.", 0x00);
      delay(750);
    }
  }

  char msg[50];
  sprintf(msg, "Continue with action %s?", action_str_repr(action));

  if (!itf.get_bool(msg, action))
  {
    itf.info("Canceled.", 0x06);
    return;
  }

  itf.message("Operating...");

  for (uint8_t i = 0; i < 4; ++i)
  {
    itf.set_leds(0x08 >> i);
    delay(500);
  }

  char *action_str = action_str_repr(action);

  if ((*func)())
  {
    sprintf(msg, "Operation %s succeeded!", action_str);
    itf.info(msg, 0x0F);
    delay(750);
    itf.set_leds(0x00);
  }
  else
  {
    sprintf(msg, "Operation %s failed!", action_str);
    itf.info(msg, 0x0A);
    delay(750);
    itf.set_leds(0x05);
    delay(750);
    itf.set_leds(0x0A);
    delay(750);
    itf.set_leds(0x05);
    delay(750);
    itf.set_leds(0x00);
  }
}

uint8_t get_value(const char *prompt1, uint8_t prompt2)
{
  while (true)
  {
    uint8_t res = itf.get_int(prompt1, prompt2);

    if (itf.get_bool("Are you sure?", 0x0F))
    {
      itf.info("Ok.", 0x00);
      return res;
    }
  }
}

bool do_action_write()
{
  char msg[50];
  sprintf(msg, "Writing file #%d to slot #%d...", file, slot);
  itf.info(msg, 0x08);

  /* TODO */

  itf.info("Done!", 0x0F);
  delay(750);
  if (itf.get_bool("Would you like to verify?", 0x04))
  {
    return do_action_read();
  }
  else
  {
    itf.info("Ok.", 0x00);
    return true;
  }
}

bool do_action_read()
{
  char msg[50];
  sprintf(msg, "Reading from slot #%d...", slot);
  itf.info(msg, 0x04);

  /* TODO */

  itf.info("Done!", 0x0F);
  delay(750);
  itf.set_leds(0x00);

  return true;
}

bool do_action_vector()
{
  char msg[50];
  sprintf(msg, "Setting vector #%d to point to slot #%d...", vector, slot);
  itf.info(msg, 0x02);

  /* TODO */

  itf.info("Done!", 0x0F);
  delay(750);
  if (itf.get_bool("Would you like to verify?", 0x04))
  {
    return do_action_read();
  }
  else
  {
    itf.info("Ok.", 0x00);
    return true;
  }
}
