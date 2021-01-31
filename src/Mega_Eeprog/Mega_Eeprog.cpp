#include <Arduino.h>

#include "Mega_Eeprog.hpp"

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
  else
  {
    return "<illegal>";
  }
}
