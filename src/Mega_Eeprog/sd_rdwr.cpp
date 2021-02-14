#include <Arduino.h>

#include <SD.h>

#include "sd_rdwr.hpp"

void sd_read(uint8_t f_id, int16_t *buf)
{
  char fname[20];
  sprintf(fname, "FILE_%X.BIN", f_id);

  uint8_t i = 0;

  File f = SD.open(fname, O_READ);

  if (f)
  {
    while (f.available())
    {
      buf[i] = f.read();

      if (i++ == 0xFF) break;
    }

    buf[i] = -1;

    f.close();
  }
  else
  {
    open_fail(fname);
  }
}

void sd_save(uint8_t *buf)
{
  File f;
  f = SD.open("SAVE.BIN", O_WRITE | O_TRUNC | O_CREAT);

  uint8_t i = 0;

  if (f)
  {
    while (true)
    {
      f.write(buf[i]);

      if (i++ == 0xFF) break;
    }

    f.close();
  }
  else
  {
    open_fail("SAVE.BIN");
  }
}

void open_fail(const char *fname)
{
  char errmsg[20];
  sprintf(errmsg, "Error opening file %s.", fname);
  Serial.println(errmsg);
}
