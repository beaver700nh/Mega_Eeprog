#include <Arduino.h>

#include "interface.hpp"
#include "number_input.hpp"

Interface::Interface() : m_in(false, 25)
{
  /* empty ctor */
}

void Interface::begin()
{
  Serial.begin(115200);

  while (!Serial) {
    /* wait for Serial connection */;
  }

  m_in.begin();
  m_out.begin();
}

void Interface::info(char *msg1, uint8_t msg2)
{
  Serial.println(msg1);
  m_out.show(msg2);
}

bool Interface::get_bool(char *msg1, uint8_t msg2)
{
  info(msg1, msg2);

  while (true)
  {
    m_in.update();

    uint8_t s = m_in.get_status();

    if (s & UP_PRESSED)
    {
      return true;
    }
    else if (s & DN_PRESSED)
    {
      return false;
    }
  }
}

uint8_t Interface::get_int(char *msg1, uint8_t msg2)
{
  info(msg1, msg2);

  uint8_t i = 0x00;

  while (true)
  {
    m_in.update();

    uint8_t s = m_in.get_status();

    if (s & UP_PRESSED)
    {
      i = (i == 0x0F ? 0x00 : ++i);
      m_out.show(i);
    }
    else if (s & DN_PRESSED)
    {
      i = (i == 0x00 ? 0x0F : --i);
      m_out.show(i);
    }
    else if (s & SEL_PRESSED)
    {
      return i;
    }
  }
}
