#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include<model/Tile.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<model/Powerup.h>
#include<model/Bullet.h>
#include<model/Enemy.h>
#include<observers/GameEventMonitor.h>
#include<vector>
#include<string>

class Board {
 private:


  class EnemySpawner : public GameEventMonitor {
 private:
   Board &board;
 public:
   EnemySpawner(Board &board);
   void tick();
   int spawnRate;
   int ticksSinceSpawnLeft;
   int ticksSinceSpawnRight;
 };
 EnemySpawner enemySpawner;

  std::vector<Tile> tiles;
  std::vector<Ball> balls;
  std::vector<Bullet> bullets;
  std::vector<Powerup> powerups;
  std::vector<GameEventMonitor *> monitors;
  std::vector<Enemy> enemies;

  Paddle player;
  int width, height;
  void collisionLogic();
  void loadTiles(std::string filename);
  void reportDeath();
  void reportTileDestruction(int id);
  void reportTileHit(int id);
  void reportPowerupDestroyed(int id);

  void collideBallsWithBorders();
  void collideBallsWithPlayer();
  void collidePlayerWithBorders();
  void collideBallsWithTiles();
  void collidePlayerWithPowerups();
  void collideBulletsWithTiles();
  void collideBallsWithEnemies();
  void collidePlayerWithEnemies();
  void collideBulletsWithEnemies();
  void consumePowerup(Powerup &powerup);


 public:
  Board(int width, int height);
  void addMonitor(GameEventMonitor *gem);
  void unstickBalls();

  void fireBullets();

  void resetBoard(std::string filename);
  void tick();
  void disruptionPowerup();

  bool gameWon();
  bool gameLost();
  std::vector<Ball> &getBalls();
  std::vector<Tile> &getTiles();
  std::vector<Powerup> &getPowerups();
  std::vector<Bullet> &getBullets();
  std::vector<Enemy> &getEnemies();
  Tile &getTile(int num);
  Paddle &getPaddle();
  int numTiles();
  int numBalls();
  void spawnEnemy(bool left);
};

#endif
