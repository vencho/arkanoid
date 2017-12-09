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
  std::vector<Paddle> paddles;

  const static int respawnTimeInFrames = 60;

  int width, height;
  void loadTiles(std::string filename);

  void reportDeath() const;
  void reportTileHit(int id) const;

  void reportTileEnters(const Tile &tile) const;
  void reportTileLeaves(const Tile &tile) const;
  void reportEnemyEnters(const Enemy &enemy) const;
  void reportEnemyLeaves(const Enemy &enemy) const;
  void reportBallEnters(const Ball &ball) const;
  void reportBallLeaves(const Ball &ball) const;
  void reportPowerupEnters(const Powerup &powerup) const;
  void reportPowerupLeaves(const Powerup &powerup) const;
  void reportBulletEnters(const Bullet &bullet) const;
  void reportBulletLeaves(const Bullet &bullet) const;
  void reportTileHit(const Tile &tile) const;

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
  void spawnBall();
  void destroyTile(Tile &tile, int index);
 public:
  const static int playAreaWidth = 13*Tile::tilePhysicalWidth;
  const static int playAreaHeight = 28*Tile::tilePhysicalHeight;

  Board();
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
  const std::vector<Paddle> &getPaddles() const;
  Paddle &player;
  const Paddle &getPaddle() const;
  Paddle &getPaddle();
};

#endif
