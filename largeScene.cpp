//18446744073709551615 max 64 bit unsigned int
//size_t on 64 bit is the same as unsigned long long int but better and easier to write

#include <iostream>

class LargeScene {
  private:
    size_t cellSizeX; //size of every cell of the scene on the x axis
    size_t cellSizeY; //size of every cell of the scene on the y axis
    size_t cellNumX; //number of cells on the x axis
    size_t cellNumY; //number of cells on the y axis
    size_t positionCellSizeX; //position inside a cell on the x axis
    size_t positionCellSizeY; //position inside a cell on the y axis
    size_t positionCellNumX; //position on the cell grid on the x axis
    size_t positionCellNumY; //position on the cell grid on the y axis
  public:
    LargeScene(size_t param_cellSizeX, size_t param_cellSizeY, size_t param_cellNumX, 
               size_t param_cellNumY, size_t param_positionCellSizeX, 
               size_t param_positionCellSizeY, size_t param_positionCellNumX, 
               size_t param_positionCellNumY) : cellSizeX(param_cellSizeX), 
                      cellSizeY(param_cellSizeY), cellNumX(param_cellNumX), 
                      cellNumY(param_cellNumY), positionCellSizeX(param_positionCellSizeX), 
                      positionCellSizeY(param_positionCellSizeY),
                      positionCellNumX(param_positionCellNumX), 
                      positionCellNumY(param_positionCellNumY) {}
    void setPosition(size_t positionCellSizeX, size_t positionCellSizeY, 
                     size_t positionCellNumX, size_t positionCellNumY);
    void moveDistance(size_t x, size_t y);
    void printLocation();
};

void LargeScene::setPosition(size_t positionCellSizeX, size_t positionCellSizeY,
                             size_t positionCellNumX, size_t positionCellNumY) {
  this->positionCellSizeX = positionCellSizeX;
  this->positionCellSizeY = positionCellSizeY;
  this->positionCellNumX = positionCellNumX;
  this->positionCellNumY = positionCellNumY;
}

void LargeScene::moveDistance(size_t x, size_t y) { //assume x/y isn't big enough to cross multiple cells at once
  if(x > 0) {
    bool error = false;
    size_t test = x;
    for(size_t a = positionCellSizeX; test > 0; ++a) {
      if(a == 0) {
        error = true;
        break;
      }
    }
    if((x + positionCellSizeX) > cellSizeX || error) {
      ++positionCellNumX;
      positionCellSizeX = x - cellSizeX;
    }
  }
  //continue here
}
