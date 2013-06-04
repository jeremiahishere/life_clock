
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

//initialize the main board arrays
//at some point, initialize the leds and chronodot
void setup() {
  Serial.begin(9600);
  initializeBoard();
  //create an r pentomino to test the algorithm
  testBoardSetup();
  
  hours = 12;
  minutes = 30;
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
  //increase time by 1 minute (for now)
  incrementTime();
  //write time to the game of life board
  //eventually only write every few ticks instead of every tick
  writeTime();   

  delay(2000);
}



