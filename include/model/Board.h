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
  void loadTiles(std::string filename);

  void reportDeath() const;
  void reportTileDestruction(int id) const;
  void reportTileHit(int id) const;
  void reportPowerupDestroyed(int id) const;
  void reportEnemyDestroyed(Enemy &enemy) const;
  
  void collisionLogic();
  void collideBallsWithBorders();
  void collideBallsWithPlayer();
  void collidePlayerWithBorders();
  void collideBallsWithTiles();
  void collidePlayerWithPowerups();
  void collideBulletsWithTiles();
  void collideBallsWithEnemies();
  void collidePlayerWithEnemies();
  void collideBulletsWithEnemies();

  void startDisruption();
  void consumePowerup(Powerup &powerup);
  void spawnEnemy(bool left);
  void destroyTile(int index);
 public:
  Board(int width, int height);
  void addMonitor(GameEventMonitor *gem);
  void unstickBalls();
  void fireBullets();
  void resetBoard(std::string filename);
  void tick();
  void consumePowerup(char type);

  const std::vector<Ball> &getBalls() const;
  const std::vector<Tile> &getTiles() const;
  const std::vector<Powerup> &getPowerups() const;
  const std::vector<Bullet> &getBullets() const;
  const std::vector<Enemy> &getEnemies() const;
  const Paddle &getPaddle() const;
  Paddle &getPaddle();
};

#endif
