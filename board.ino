//hard coded board size
const int boardWidth = 32;
const int boardContainerWidth = 4;
const int boardHeight = 24;
//the game of life board
//two boards that switch back and forth
int board[2][24][4];
int currentBoard = 0;

//zero out both boards
void initializeBoard()  {
  for(int i = 0; i < 2; i++)  {
    for(int j = 0; j < boardHeight; j++)  {
      for(int k = 0; k < boardContainerWidth; k++)  {
        board[i][j][k] = B00000000;
      }
    }
  }
}

//add some things to the board for testing
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
  setNextCell(16, 2, true);
  setNextCell(16, 3, true);
  setNextCell(16, 4, true);
  setNextCell(17, 2, true);
  setNextCell(15, 3, true);
}

//switch which board is the current one
void switchBoard()  {
  if(currentBoard == 1)  {
    currentBoard = 0;
  } else {
    currentBoard = 1;
  }
}

//get the next board from the current one
int getNextBoard()  {
  if(currentBoard == 1)  {
    return 0;
  } else {
    return 1;
  }
}

//set a cell on the current board
void setCurrentCell(int x, int y, boolean value)  {
  setCell(currentBoard, x, y, value);
}

//set a cell on the next board
void setNextCell(int x, int y, boolean value)  {
  setCell(getNextBoard(), x, y, value);
}

//set a cell on either board
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

//set a rectangle on the board all to the same value
void setRectangle(int boardId, int startX, int startY, int width, int height, boolean value)  {
  for(int i = startY; i < startY + height; i++)  {
    for(int j = startX; j < startX + width; j++)  {
      setCell(boardId, j, i, value);
    }
  }
}

//get the value of a cell from the board
boolean getCell(int x, int y)  {
  if(x >= 0 && y >= 0 && x < boardWidth && y < boardHeight)  {
    int containerId = x / 8;
    int maskId = x % 8;
    
    return (board[currentBoard][y][containerId] & cellMask[maskId]) >> maskId;
  } else {
    return false;
  }
}

//get the number of neighbors of a cell
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

//do a game of life generation on one cell and set the next board
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

//do a game of life generation on the current board
void iterateBoard()  {
  for(int i = 0; i < boardHeight; i++)  {
    for(int j = 0; j < boardWidth; j++)  {
      iterateCell(j, i);
    }
  }
}

//write board to serial out
void writeBoard()  {
  for(int i = 0; i < boardHeight; i++)  {
    for(int j = 0; j < boardWidth; j++) {
      Serial.print(getCell(j, i));
    }
    Serial.print("\n");
  }
  Serial.print("\n\n\n");
}
