#include<Tile.h>
#include<Ball.h>
#include<Paddle.h>
#include<vector>
#include<string>

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board {
 private:
  std::vector<Tile> tiles;
  std::vector<Ball> balls;
  Paddle player;
  int width, height;
  void collisionLogic();
  void loadTiles(std::string filename);

 public:
  void initialiseBalls();
  bool gameWon();
  bool gameLost();
  void report();
  void tick();
  Board(int width, int height, std::string filename);
  Ball &getBall(int num);
  Tile &getTile(int num);
  Paddle &getPaddle();
  int numTiles();

};

#endif
