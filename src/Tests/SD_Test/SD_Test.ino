#include <SPI.h>
#include <SD.h>
#include "pin_constants.hpp"

File myFile;

void write_test() {
  myFile = SD.open("test.txt", O_WRITE | O_TRUNC);

  if (myFile) {
    Serial.println("Writing to test.txt...");

    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");
    myFile.println("Hello, World!");

    for (int i = 0; i < 20; i++) {
      myFile.println(i);
    }

    myFile.close();

    Serial.println("done.");
  }
  else {
    Serial.println("error opening test.txt");
  }
}

void read_test() {
  myFile = SD.open("test.txt", O_READ);

  if (myFile) {
    Serial.println("Reading from test.txt...");

    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    myFile.close();
    Serial.println("done.");
  }
  else {
    Serial.println("error opening test.txt");
  }
}

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    /* wait for Serial connection */;
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CS)) {
    Serial.println(" failed!");
    while (true) {
      /* freeze */;
    }
  }
  else {
    Serial.println(" success!");
  }

  Serial.println("initialization done.");

  write_test();
  read_test();
}
int i = 0;
void loop() {
//  if (i == 0) {
//    //write_test();
//    read_test();
//    i++;
//  }
  /* empty loop */;
}
