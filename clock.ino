//location of digits on the led display
const int HOURS_DIGIT_2 = 1;
const int HOURS_DIGIT_1 = 2;
const int MINUTES_DIGIT_2 = 3;
const int MINUTES_DIGIT_1 = 4;
const int SECONDS_DIGIT_2 = 5;
const int SECONDS_DIGIT_1 = 6;

//the font system
//font stolen from http://www.dafont.com/texas-led.font
const int digitHeight = 7;
const int digitWidth = 5;
//note that only the first five bits are used in each number
const int digits[10][digitHeight] = {
  { //zero
    B01110000,
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000
  },
  { //one
    B00100000,
    B01100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B01110000
  },
  { //two
    B01110000,
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000
  },
  { //three
    B11111000,
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000
  },
  { //four
    B00010000,
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000
  },
  { //five
    B11111000,
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000
  },
  { //six
    B00110000,
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000     
  },
  { //seven
    B11111000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B01000000,
    B01000000
  },
  { //eight
    B01110000,
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000
  },
  { //nine
    B01110000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000
  }
};

//updates the time from the chronodot
//returns true if there is a change
boolean updateTime()  {
  DateTime now = RTC.now();
 
  if(now.second() != seconds)  {
    hours = now.hour();
    minutes = now.minute();
    seconds = now.second();
    return true;
  }
  return false;
}
  
//add one minute to the time
//used to manualy change the time
void incrementTime()  {
  seconds += 1;
  if(seconds > 59)  {
    seconds = 0;
    minutes += 1;
  }
  if(minutes > 59)  {
    minutes = 0;
    hours += 1;
  }
  if(hours > 12)  {
    hours = 1;
  }
}

//write the time to the game of life board
void writeTime()  {
  //depending on integer division dropping remainders here
  
  //hours digit 2
  //do not write if not in use
  if(hours / 10 > 0)  {
    writeDigit(hours / 10, HOURS_DIGIT_2);
  }
  //hours digit 1
  writeDigit(hours % 10, HOURS_DIGIT_1);
  //minutes digit 2
  writeDigit(minutes / 10, MINUTES_DIGIT_2);
  //minutes digit 1
  writeDigit(minutes % 10, MINUTES_DIGIT_1);
  //seconds digit 2
  writeDigit(seconds / 10, SECONDS_DIGIT_2);
  //seconds digit 1
  writeDigit(seconds % 10, SECONDS_DIGIT_1);
}

//write a digit to the game of life board
void writeDigit(int x, int position)  {
  int startX;
  int startY;

  if(position == HOURS_DIGIT_2)  {
    startX = 2; startY = 5;    
  } else if(position == HOURS_DIGIT_1) {
    startX = 9; startY = 5;
  } else if(position == MINUTES_DIGIT_2)  {
    startX = 18; startY = 5;
  } else if(position == MINUTES_DIGIT_1)  {
    startX = 25; startY = 5;
  } else if(position == SECONDS_DIGIT_2)  {
    startX = 34; startY = 5;
  } else if(position == SECONDS_DIGIT_1)  {
    startX = 41; startY = 5;
  }
  //blank the area
  setRectangle(getNextBoard(), startX-1, startY-1, digitWidth+2, digitHeight+2, false);
 
  for(int i = 0; i < digitHeight; i++)  {
    for(int j = 0; j < digitWidth; j++)  {
      int bitOffset = 7 - j;
      //dont need to shift by the bitOffset here, the mask should resolve to 0 or a positive integer which evaluates to false/true
      //keeping it here for consistency
      boolean value = (digits[x][i] & cellMask[bitOffset]) >> bitOffset;
      setNextCell(j + startX, i + startY, value);
    }
  }
}
