#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include<Tile.h>
#include<Ball.h>
#include<Paddle.h>
#include<vector>
#include<string>
#include<DeathMonitor.h>
#include<TileDestructionMonitor.h>

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
  void addTileDestructionMonitor(TileDestructionMonitor *tdm);
  void addDeathMonitor(DeathMonitor *dm);
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
