#ifndef MEGA_EEPROG_HPP
#define MEGA_EEPROG_HPP

#include <Arduino.h>

#define ACTION_WRITE  0x08
#define ACTION_READ   0x04
#define ACTION_VECTOR 0x02

char *action_str_repr(uint8_t action);

#endif
