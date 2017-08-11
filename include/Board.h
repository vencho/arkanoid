#include<Tile.h>
#include<Ball.h>
#include<Paddle.h>
#include<vector>

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board {
 private:
  std::vector<Tile> tiles;
  std::vector<Ball> balls;
  Paddle player;
  int width, height;
  void collisionLogic();

 public:
  bool gameWon();
  bool gameLost();
  void report();
  void tick();
  Board(int width, int height);
  Ball &getBall(int num);
  Tile &getTile(int num);
  Paddle &getPaddle();
  int numTiles();

};

#endif
