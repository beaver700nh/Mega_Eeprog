#include <SD.h>
#include <Bounce2.h>
#include "pin_constants.hpp"

uint8_t current_val = 0x00;

Bounce *buttons[] = {
  new Bounce(),
  new Bounce(),
  new Bounce()
};

File myFile;

void write_program_id(uint8_t id);
void log_sd(uint8_t val);

void setup()
{
  Serial.begin(57600);

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(RW_SIG, OUTPUT);

  uint8_t pins[] = {BTN_UP, BTN_DN, BTN_SEL};

  for (uint8_t i = 0; i < 3; ++i) {
    buttons[i]->attach(pins[i], INPUT_PULLUP);
    buttons[i]->interval(5);
  }
}

void loop()
{
  for (uint8_t i = 0; i < 3; ++i) {
    buttons[i]->update();
  }

  if (buttons[0]->fell()) {
    ++current_val;
  }
  else if (buttons[1]->fell()) {
    --current_val;
  }

  if (buttons[2]->fell()) {
    digitalWrite(RW_SIG, HIGH);
    log_sd(current_val);
    digitalWrite(RW_SIG, LOW);
  }

  write_program_id(current_val);
}

void write_program_id(uint8_t id) {
  digitalWrite(LED_0, id & 0x01);
  digitalWrite(LED_1, id & 0x02);
  digitalWrite(LED_2, id & 0x04);
  digitalWrite(LED_3, id & 0x08);
}

void log_sd(uint8_t val) {
  if (SD.begin(SD_CS)) {
    myFile = SD.open("log.txt", FILE_WRITE);

    if (myFile) {
      myFile.println(val);
      myFile.close();
    }
  }
}
