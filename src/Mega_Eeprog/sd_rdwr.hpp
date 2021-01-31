#ifndef SD_RDWR_HPP
#define SD_RDWR_HPP

#include <Arduino.h>

void sd_read(uint8_t f_id, uint8_t *buf);
void sd_save(uint8_t *buf);

#endif
