#ifndef NUMBER_INPUT_HPP
#define NUMBER_INPUT_HPP

#include <Arduino.h>
#include <Bounce2.h>

#include "pin_constants.hpp"

class InputBtns {
  private:
    bool m_available = false;
    bool m_selected = false;

    uint8_t m_val = 0;

    bool m_use_extern_resistors;
    int m_interval;

    Bounce *m_buttons[3] = {
      new Bounce(),
      new Bounce(),
      new Bounce()
    };

  public:
    InputBtns(bool uer, int itv);

    void begin();

    void update();
    bool available();
    bool selected();
    int8_t get_val();
};

class OutputLeds {
  public:
    OutputLeds();

    void begin();

    void show(uint8_t val);
};

#endif
