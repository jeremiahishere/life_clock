

const int boardWidth = 32;
const int boardContainerWidth = 4;
const int boardHeight = 24;

int cellMask[8];
int board[2][24][4];
int currentBoard = 0;

void setup() {
  Serial.begin(9600);
  initializeBoard();
  initializeCellMask();
  testBoardSetup();
}

void initializeBoard()  {
  for(int i = 0; i < 2; i++)  {
    for(int j = 0; j < boardHeight; j++)  {
      for(int k = 0; k < boardContainerWidth; k++)  {
        board[i][j][k] = B00000000;
      }
    }
  }
}

void initializeCellMask()  {
  cellMask[0] = B00000001;
  cellMask[1] = B00000010;
  cellMask[2] = B00000100;
  cellMask[3] = B00001000;
  cellMask[4] = B00010000;
  cellMask[5] = B00100000;
  cellMask[6] = B01000000;
  cellMask[7] = B10000000;
}

void testBoardSetup()  {
  //line oscillator
  /*
  setNextCell(16, 12, true);
  setNextCell(16, 13, true);
  setNextCell(16, 14, true);*/
  
  //glider
  /*
  setNextCell(14, 13, true);
  setNextCell(15, 14, true);
  setNextCell(16, 12, true);
  setNextCell(16, 13, true);
  setNextCell(16, 14, true);*/
  
  //r pentomino
  setNextCell(16, 12, true);
  setNextCell(16, 13, true);
  setNextCell(16, 14, true);
  setNextCell(17, 12, true);
  setNextCell(15, 13, true);
}

void loop()  {
  switchBoard();
  writeBoard();
  iterateBoard();  
  delay(2000);
}

void switchBoard()  {
  if(currentBoard == 1)  {
    currentBoard = 0;
  } else {
    currentBoard = 1;
  }
}

int getNextBoard()  {
  if(currentBoard == 1)  {
    return 0;
  } else {
    return 1;
  }
}

void setCurrentCell(int x, int y, boolean value)  {
  setCell(currentBoard, x, y, value);
}

void setNextCell(int x, int y, boolean value)  {
  setCell(getNextBoard(), x, y, value);
}

void setCell(int boardId, int x, int y, boolean value)  {
  if(x >= 0 && y >= 0 && x < boardWidth && y < boardHeight)  {
    int containerId = x / 8;
    int maskId = x % 8;
    
    if(value)  {
      board[boardId][y][containerId] = board[boardId][y][containerId] | cellMask[maskId];
    } else {
      board[boardId][y][containerId] = board[boardId][y][containerId] & ~cellMask[maskId];
    }
  }
}

boolean getCell(int x, int y)  {
  if(x >= 0 && y >= 0 && x < boardWidth && y < boardHeight)  {
    int containerId = x / 8;
    int maskId = x % 8;
    
    return (board[currentBoard][y][containerId] & cellMask[maskId]) >> maskId;
  } else {
    return false;
  }
}

int getCellNeighborCount(int x, int y)  {
  int count = 0;
  
  //upper row
  if(getCell(x-1, y-1))  { count++; }
  if(getCell(x, y-1))  { count++; }
  if(getCell(x+1, y-1))  { count++; }
  //current row
  if(getCell(x-1, y))  { count++; }
  if(getCell(x+1, y))  { count++; }
  //lower row
  if(getCell(x-1, y+1))  { count++; }
  if(getCell(x, y+1))  { count++; }
  if(getCell(x+1, y+1))  { count++; }
  
  return count;
}

void iterateCell(int x, int y)  {
  int alive = getCell(x, y);
  int neighbors = getCellNeighborCount(x, y);
  
  if(alive)  {
    if(neighbors == 2 || neighbors == 3)  {
      setNextCell(x, y, true);
    } else {
      setNextCell(x, y, false);
    }
  } else {
    if(neighbors == 3)  {
      setNextCell(x, y, true);
    } else {
      setNextCell(x, y, false);
    }
  }
}

void iterateBoard()  {
  for(int i = 0; i < boardHeight; i++)  {
    for(int j = 0; j < boardWidth; j++)  {
      iterateCell(j, i);
    }
  }
}

void writeBoard()  {
  for(int i = 0; i < boardHeight; i++)  {
    for(int j = 0; j < boardWidth; j++) {
      Serial.print(getCell(j, i));
    }
    Serial.print("\n");
  }
  Serial.print("\n\n\n");
}
