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

//the current time
int hours;
int minutes;
int tick;

//initialize the main board arrays
//at some point, initialize the leds and chronodot
void setup() {
  Serial.begin(9600);
  initializeBoard();
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen(); 
  //create an r pentomino to test the algorithm
  //testBoardSetup();
  
  hours = 12;
  minutes = 30;
  tick = 1;
}

void loop()  {
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print("\n");
  
  //shange next board to the current board
  switchBoard();
  //write to serial port (eventually to led)
  writeBoard();
  //iterate the game of life
  iterateBoard();
  
  
  //write time to the game of life board
  //eventually only write once a second instead of every few ticks
  if(tick%5 == 0)  {
    //increase time by 1 minute (for now)
    incrementTime();
    writeTime();
    tick = 1;
  } else {
   tick += 1;
  } 

  delay(10);
}



