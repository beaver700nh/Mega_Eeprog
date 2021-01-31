#include "Mega_Eeprog.hpp"
#include "eeprom_controller.hpp"
#include "pin_constants.hpp"
#include "interface.hpp"
#include "prpr.hpp"

EepromController ec(EEPROM_WE_B);

uint8_t file, page_hi, page_lo, vector;

uint8_t get_value(const char *prompt1, uint8_t prompt2);

bool do_action_write();
bool do_action_read();
bool do_action_vector();

Interface itf;

bool (*func)();

void setup()
{
  delay(1000);

  ec.begin();

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
      page_hi = get_value("Select page to write to. (NNNNxxxx)", 0x09);
      page_lo = get_value("Select page to write to. (xxxxNNNN)", 0x09);
      func = do_action_write;
      break;
    }
    else if (action == ACTION_READ)
    {
      page_hi = get_value("Select page to read from. (NNNNxxxx)", 0x05);
      page_lo = get_value("Select page to read from. (xxxxNNNN)", 0x05);
      func = do_action_read;
      break;
    }
    else if (action == ACTION_VECTOR)
    {
      vector = get_value("Select vector to set.", 0x09);
      page_hi = get_value("Select page to jump to. (NNNNxxxx)", 0x03);
      page_lo = get_value("Select page to jump to. (xxxxNNNN)", 0x03);
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
  sprintf(msg, "Writing file #%d to page %02x%02x", file, page_hi, page_lo);
  itf.info(msg, 0x08);

  if (page_hi >= 8)
  {
    itf.info("Invalid page.", 0x06);
    return false;
  }

  uint8_t buf[0xFF];
  sd_read(file, buf);

  uint8_t i = 0;

  while (true)
  {
    ec.set_eeprom((page_hi << 12) | (page_lo << 8) | i, buf[i]);

    if (i++ == 0xFF) break;
  }

  itf.info("Done!", 0x0F);
  delay(750);
  if (itf.get_bool("Would you like to verify?", 0x04))
  {
    do_action_read();
  }
  else
  {
    itf.info("Ok.", 0x00);
  }

  return true;
}

bool do_action_read()
{
  char msg[50];
  sprintf(msg, "Reading from page %01x%01x", page_hi, page_lo);
  itf.info(msg, 0x04);
  delay(750);

  if (page_hi >= 8)
  {
    itf.info("Invalid page.", 0x06);
    return false;
  }

  uint8_t i = 0;
  uint8_t data[0xFF];

  while (true)
  {
    data[i] = ec.get_eeprom((page_hi << 12) | (page_lo << 8) | i);

    if (i++ == 0xFF) break;
  }

  prpr_data(data);
  sd_save(data);

  itf.info("Done!", 0x0F);
  delay(750);
  itf.set_leds(0x00);

  return true;
}

bool do_action_vector()
{
  char msg[50];
  sprintf(msg, "Setting vector 7ff%01x to point to page %01x%01x", vector, page_hi, page_lo);
  itf.info(msg, 0x02);

  if (vector < 0x0A)
  {
    itf.info("Invalid vector.", 0x06);
    return false;
  }

  ec.set_eeprom(0x7FF0 | vector, 0x00);
  ec.set_eeprom(0x7FF0 | (vector + 1), (page_hi << 4) | page_lo);

  itf.info("Done!", 0x0F);
  delay(750);
  if (itf.get_bool("Would you like to verify?", 0x04))
  {
    page_hi = 0x07;
    page_lo = 0x0f;
    do_action_read();
  }
  else
  {
    itf.info("Ok.", 0x00);
  }

  return true;
}
