//setup for matrix
#include <HT1632.h>
#define DATA 2
#define WR   3
#define CS   4
#define CS2  5
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

//mask used to pull boolean values out of integers
int cellMask[8] = {
  cellMask[0] = B00000001,
  cellMask[1] = B00000010,
  cellMask[2] = B00000100,
  cellMask[3] = B00001000,
  cellMask[4] = B00010000,
  cellMask[5] = B00100000,
  cellMask[6] = B01000000,
  cellMask[7] = B10000000
};

//setup for chronodot
#include <Wire.h>
#include "Chronodot.h"
Chronodot RTC;


//the current time
int hours;
int minutes;
int seconds;
int tick;

//initialize the main board arrays
//at some point, initialize the leds and chronodot
void setup() {
  Serial.begin(9600);
  
  Serial.println("Initializing Chronodot.");
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");

  } else {
        // following line sets the RTC to the date & time this sketch was compiled
    Serial.println(__DATE__);
    Serial.println(__TIME__);
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  initializeBoard();
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  
  //default to midnight/noon
  //should be overriden on first call to chronodot
  hours = 12;
  minutes = 00;
  seconds = 0;
}

void loop()  {
  //update time from chronodot
  //updated should be true if time has changed
  boolean updated = updateTime();
  if(updated)  {
    writeTime();
  }  
  
  //switch current and future boards
  switchBoard();
  //write current board to matrix
  writeBoard();
  //iterate game of life on future board
  iterateBoard();
  
  if(updated)  {
    delay(400);
  } else {
    delay(1);
  }
}



