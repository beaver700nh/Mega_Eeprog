#include <SD.h>
#include <Bounce2.h>
#include "pin_constants.hpp"

char current_val = 0x00;

File myFile;

void write_program_id(uint8_t id);
void rd_sd();

void setup()
{
  Serial.begin(57600);

  while (!Serial) {
    /* wait for Serial connection */;
  }

  Serial.println("*** PROGRAM INIT ***");

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  if (SD.begin(SD_CS)) {
    Serial.println("Succeeded init SD");

    myFile = SD.open("log.txt", FILE_READ);

    if (!myFile) {
      while (true) {
        /* freeze */;
      }
    }

    Serial.println("Succeeded open file");
  }
}

void loop()
{
  //Serial.println("Reading");
  rd_sd();
  write_program_id((uint8_t) current_val);
  Serial.print(current_val);
  delay(1000);
}

void write_program_id(uint8_t id) {
  digitalWrite(LED_0, id & 0x01);
  digitalWrite(LED_1, id & 0x02);
  digitalWrite(LED_2, id & 0x04);
  digitalWrite(LED_3, id & 0x08);
}

void rd_sd() {
  if (myFile.available()) {
    //Serial.println("Available!");
    current_val = myFile.read();
  }
  else {
    while (true) {
      /* freeze */;
    }
  }
}
