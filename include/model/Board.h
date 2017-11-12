#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include<model/Tile.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<observers/DeathMonitor.h>
#include<observers/TileDestructionMonitor.h>
#include<vector>
#include<string>

class Board {
 private:
  std::vector<Tile> tiles;
  std::vector<Ball> balls;
  std::vector<DeathMonitor *> deathMonitors;
  std::vector<TileDestructionMonitor *> tileDestructionMonitors;
  
  Paddle player;
  int width, height;
  void collisionLogic();
  void loadTiles(std::string filename);
  void reportDeath();
  void reportTileDestruction();
  
 public:
  Board(int width, int height);
  void addTileDestructionMonitor(TileDestructionMonitor *tdm);
  void addDeathMonitor(DeathMonitor *dm);
  void initialiseBalls();

  void resetBoard(std::string filename);
  void tick();

  bool gameWon();
  bool gameLost();
  Ball &getBall(int num);
  Tile &getTile(int num);
  Paddle &getPaddle();
  int numTiles();
  int numBalls();
};

#endif
