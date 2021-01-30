#ifndef PIN_CONSTANTS_H
#define PIN_CONSTANTS_H

#define LED_0 32
#define LED_1 33
#define LED_2 31
#define LED_3 30

#define BTN_UP  34
#define BTN_DN  35
#define BTN_SEL 36

#define UP_PRESSED  0x04
#define DN_PRESSED  0x02
#define SEL_PRESSED 0x01

#define SHR_OE    23
#define SHR_LATCH 25

#define SD_CS 37

#define RW_SIG 49

#define EEPROM_DATA_OUT PORTF
#define EEPROM_DATA_IN  PINF
#define EEPROM_DATA_DIR DDRF

#define EEPROM_WE_A A8
#define EEPROM_WE_B 2
#define EEPROM_WE_C 22

#endif
