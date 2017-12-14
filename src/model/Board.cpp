#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<model/Powerup.h>
#include<geometry/CollisionManager.h>
#include<cstdio>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

int Board::getTicksSinceSpawnLeft() const {
  return ticksSinceEnemySpawnedLeft;
}

int Board::getTicksSinceSpawnRight() const {
  return ticksSinceEnemySpawnedRight;
}

void Board::fireBullets() {
  if(!player.canFire()) return;
  bullets.emplace_back(player, true);
  reportBulletEnters(bullets.back());
  bullets.emplace_back(player, false);
  reportBulletEnters(bullets.back());
  player.fire();
}

void Board::collideBulletsWithEnemies() {
  for(int i = 0; i < bullets.size(); i++) {
    bool killBullet = false;
    for(int j = 0; j < enemies.size(); j++) {
      if(CollisionManager::rectanglesIntersect(bullets[i], enemies[j])) {
	reportEnemyLeaves(enemies[j]);
	enemies.erase(enemies.begin() + j);
	killBullet = true;
      }
    }
    if(killBullet) {
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }
}

void Board::collideBulletsWithTiles() {
  for(int i = 0; i < bullets.size(); i++) {
    Bullet &bullet = bullets[i];
    bool hitSomething = false;
    for(int j = 0; j < tiles.size(); j++) {
      Tile &tile = tiles[j];
      if(!CollisionManager::rectanglesIntersect(bullet, tile)) continue;
      hitSomething = true;
      tile.takeDamage();
      reportTileHit(tile);
      printf("Tile with id %d takes damage, health down to %d.\n", tile.getId(), tile.getHealth());
      if(tile.getHealth() == 0) {
	destroyTile(tiles[j], j);
	j--;
      }
    }
    if(hitSomething) {
      reportBulletLeaves(bullets[i]);
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }
}

void Board::collideBallsWithBorders() {
  for(int i = 0; i < balls.size(); i++) {
    CollisionManager::collideBorders(balls[i]);
  }
}

void Board::collideBallsWithPlayer() {
  for(int i = 0; i < balls.size(); i++) {
    int answerMask = CollisionManager::collideRectangle(balls[i], player, 7, 3);
    if(answerMask) {
      int stickCode;
      if(answerMask & 1) stickCode = 1;
      else if(answerMask & 2) stickCode = 2;
      else stickCode = 3;
      balls[i].modifyAngle(player);
      if(player.catchActive()) {
	balls[i].stick(player, stickCode);
      }
    }
  }
}

void Board::collidePlayerWithBorders() {
  CollisionManager::collideBorders(player);
}

void Board::collideBallsWithTiles() {
  for(int i = 0; i < balls.size(); i++) {
    std::vector<int> whichTilesHit;
    for(int j = 0; j < tiles.size(); j++) {
      Tile &tile = tiles[j];
      if(CollisionManager::rectanglesIntersect(balls[i], tile)) {
	whichTilesHit.push_back(j);
      }
    }

    if(whichTilesHit.size() != 2 ||
       (tiles[whichTilesHit[0]].getX() != tiles[whichTilesHit[1]].getX() &&
	tiles[whichTilesHit[0]].getY() != tiles[whichTilesHit[1]].getY())) {
      for(int j = 0; j < whichTilesHit.size(); j++) {
	Tile &tile = tiles[whichTilesHit[j]];
	printf("Collision with tile id %d.\n", tile.getId());
	CollisionManager::collideRectangle(balls[i], tile, 15, 3);
      }
    }
    else {
      Tile &a = tiles[whichTilesHit[0]];
      Tile &b = tiles[whichTilesHit[1]];
      printf("Collision with tiles id %d and %d simultaneously.\n", a.getId(), b.getId());
      int x, y, w, h;
      x = a.getX() < b.getX() ? a.getX() : b.getX();
      y = a.getY() < b.getY() ? a.getY() : b.getY();
      w = a.getX() == b.getX() ? a.getWidth() : a.getWidth() + b.getWidth();
      h = b.getY() == b.getY() ? a.getHeight() : a.getHeight() + b.getHeight();
      DockedRectangle rect(x, y, w, h);
      CollisionManager::collideRectangle(balls[i], rect, 15, 3);
    }

    int countRemoved = 0;
    for(int j = 0; j < whichTilesHit.size(); j++) {
      Tile &tile = tiles[whichTilesHit[j] - countRemoved];
      tile.takeDamage();
      reportTileHit(tile);
      printf("Tile with id %d takes damage, health down to %d.\n", tile.getId(), tile.getHealth());
      if(tile.getHealth() == 0) {
	destroyTile(tiles[whichTilesHit[j] - countRemoved], whichTilesHit[j] - countRemoved);
	countRemoved++;
      }
    }
  }
}

void Board::collidePlayerWithEnemies() {
  for(int i = 0; i < enemies.size(); i++) {
    if(CollisionManager::rectanglesIntersect(player, enemies[i])) {
      reportEnemyLeaves(enemies[i]);
      enemies.erase(enemies.begin() + i);
      i--;
    }
  }
}

void Board::collideBallsWithEnemies() {
  for(int i = 0; i < balls.size(); i++) {
    for(int j = 0; j < enemies.size(); j++) {
      int allowedReflects = balls[i].isStuck() ? 0 : 3;
      if(CollisionManager::collideRectangle(balls[i], enemies[j], 15, allowedReflects)) {
	reportEnemyLeaves(enemies[j]);
	enemies.erase(enemies.begin() + j);
	j--;
      }
    }
  }
}

void Board::collisionLogic() {
  collideBulletsWithTiles();
  collideBulletsWithEnemies();
  collideBallsWithTiles();
  collideBallsWithPlayer();
  collideBallsWithBorders();
  collideBallsWithEnemies();
  collidePlayerWithPowerups();
  collidePlayerWithEnemies();
}

void Board::collidePlayerWithPowerups() {
  for(int i = 0; i < powerups.size(); i++) {
    if(CollisionManager::rectanglesIntersect(player, powerups[i])) {
      consumePowerup(powerups[i]);
      reportPowerupLeaves(powerups[i]);
      powerups.erase(powerups.begin() + i);
      i--;
    }
  }
}

void Board::startDisruption() {
  int n = balls.size();
  for(int i = 0; i < n; i++) {
    balls.emplace_back(balls[i]);
    balls.back().assignNewId();
    balls.back().modifyAngle(M_PI/6);
    reportBallEnters(balls.back());
    balls.emplace_back(balls[i]);
    balls.back().assignNewId();
    balls.back().modifyAngle(-M_PI/6);
    reportBallEnters(balls.back());
  }
}

void Board::consumePowerup(char type) {
  if(type == 'E') player.startEnlarge();
  else if(type == 'C') player.startCatch();
  else if(type == 'S') Ball::startSlow();
  else if(type == 'D') startDisruption();
  else if(type == 'L') player.startLaser();
}

void Board::consumePowerup(Powerup &powerup) {
  printf("Consumed powerup with id %d of type %c.\n", powerup.getId(), powerup.getType());
  consumePowerup(powerup.getType());
}

void Board::destroyTile(Tile &tile, int idx) {
  printf("Erasing tile with id %d.\n", tiles[idx].getId());
  bool spawnPowerup = (rand() % Configuration::powerupSpawnRate == 0 && powerups.size() < Configuration::maxPowerupsOnScreen);
  char powerupLetter;
  switch(rand() % 7) {
  case 0:
    powerupLetter = 'L'; break;
  case 1:
    powerupLetter = 'E'; break;
  case 2:
    powerupLetter = 'C'; break;
  case 3:
    powerupLetter = 'S'; break;
  case 4:
    powerupLetter = 'D'; break;
  case 5:
    powerupLetter = 'B'; break;
  case 6:
    powerupLetter = 'P'; break;
  }
  reportTileLeaves(tile);
  if(spawnPowerup) powerups.emplace_back(tile, powerupLetter);
  tiles.erase(tiles.begin() + idx);
  if(spawnPowerup) reportPowerupEnters(powerups.back());
}

Board::Board() : paddles(1, Paddle()), player(paddles[0]) {
}

void Board::spawnBall() {
  balls.emplace_back(player);
  reportBallEnters(balls.back());
}

void Board::resetBoard(std::string filename) {
  enemies.clear();
  powerups.clear();
  bullets.clear();

  balls.clear();
  spawnBall();
  Ball::stopSlow();

  loadTiles(filename);

  player.reset();

  ticksSinceEnemySpawnedLeft = 0;
  ticksSinceEnemySpawnedRight = Configuration::enemySpawnRate / 2;
}

int Board::colourOf(const std::string &word) const {
  if(word == "white") return 0;
  else if(word == "orange") return 1;
  else if(word == "cyan") return 2;
  else if(word == "red") return 3;
  else if(word == "blue") return 4;
  else if(word == "pink") return 5;
  else if(word == "green") return 6;
  else if(word == "yellow") return 7;
  else if(word == "silver") return 8;
  else if(word == "golden") return 9;
  else {
    printf("unrecognised colour in level description!\n");
    return 0;
  }
}

void Board::loadTiles(const std::string &filename) {
  tiles.clear();

  bool swap = false;
  std::ifstream fin;
  fin.open(filename);
  int row, column, health, colour;
  for(int row = 1; !fin.eof(); row++) {
    std::string line;
    std::getline(fin, line);
    if(line == "SWAP") { swap ^= 1; row--; continue; }
    if(line.length() == 0 || line == "GAP") continue;
    std::istringstream lineStream(line);
    for(int column = 1; !lineStream.eof(); column++) {
      std::string word;
      lineStream >> word;
      if(word == "gap") continue;
      if(swap) {
	tiles.emplace_back(column, row, colourOf(word));
      }
      else {
	tiles.emplace_back(row, column, colourOf(word));
      }
      reportTileEnters(tiles.back());
    }
  }
  fin.close();
}

void Board::unstickBalls() {
  for(int i = 0; i < balls.size(); i++) {
    balls[i].unstick();
  }
}

void Board::addMonitor(GameEventMonitor *gem) {
  monitors.push_back(gem);
}

void Board::reportDeath() const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyDied();
  }
}

void Board::reportTileHit(const Tile &tile) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyTileHit(tile);
  }
}

void Board::reportTileEnters(const Tile &tile) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnters(tile);
  }
}

void Board::reportTileLeaves(const Tile &tile) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyLeaves(tile);
  }
}

void Board::reportBallLeaves(const Ball &ball) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyLeaves(ball);
  }
}

void Board::reportBulletEnters(const Bullet &bullet) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnters(bullet);
  }
}

void Board::reportBulletLeaves(const Bullet &bullet) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyLeaves(bullet);
  }
}

void Board::reportBallEnters(const Ball &ball) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnters(ball);
  }
}

void Board::reportPowerupEnters(const Powerup &powerup) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnters(powerup);
  }
}

void Board::reportPowerupLeaves(const Powerup &powerup) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyLeaves(powerup);
  }
}

void Board::reportEnemyEnters(const Enemy &enemy) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnters(enemy);
  }
}

void Board::reportEnemyLeaves(const Enemy &enemy) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyLeaves(enemy);
  }
}

void Board::tick() {
  static int timetorespawn = -1;
  if(balls.empty()) {
    if(timetorespawn > 0) timetorespawn--;
    else if(timetorespawn == 0) {
      reportDeath();
      spawnBall();
      timetorespawn--;
    }
    else {
      timetorespawn = respawnTimeInFrames;
    }
  }
  
  ticksSinceEnemySpawnedLeft = (ticksSinceEnemySpawnedLeft + 1) % Configuration::enemySpawnRate;
  ticksSinceEnemySpawnedRight = (ticksSinceEnemySpawnedRight + 1) % Configuration::enemySpawnRate;
  if(ticksSinceEnemySpawnedLeft == 25) spawnEnemy(true);
  if(ticksSinceEnemySpawnedRight == 25) spawnEnemy(false);

  player.tick();
  collidePlayerWithBorders();
  for(int i = 0; i < balls.size(); i++) {
    balls[i].tick();
    if(balls[i].getY() > playAreaHeight) {
      reportBallLeaves(balls[i]);
      balls[i] = balls.back();
      balls.pop_back();
      i--;
    }
  }
  Ball::tickSlow();
  
  for(int i = 0; i < bullets.size(); i++) {
    bullets[i].tick();
    if(CollisionManager::collideBorders(bullets[i])) {
      reportBulletLeaves(bullets[i]);
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }

  for(int i = 0; i < enemies.size(); i++) {
    enemies[i].tick();
  }

  collisionLogic();

  for(int i = 0; i < powerups.size(); i++) {
    powerups[i].tick();
    if(powerups[i].getY() > playAreaHeight) {
      printf("Powerup with id %d and type %c has left the screen.\n", powerups[i].getId(), powerups[i].getType());
      reportPowerupLeaves(powerups[i]);
      powerups.erase(powerups.begin() + i);
      i--;
    }
  }
}


const std::vector<Ball> &Board::getBalls() const {
  return balls;
}

const std::vector<Bullet> &Board::getBullets() const {
  return bullets;
}

const std::vector<Tile> &Board::getTiles() const {
  return tiles;
}

const Paddle &Board::getPaddle() const {
  return player;
}

Paddle &Board::getPaddle() {
  return player;
}

const std::vector<Powerup> &Board::getPowerups() const {
  return powerups;
}

const std::vector<Enemy> &Board::getEnemies() const {
  return enemies;
}

const std::vector<Paddle> &Board::getPaddles() const {
  return paddles;
}

void Board::spawnEnemy(bool left) {
  if(left) enemies.emplace_back(132 - Enemy::enemyPhysicalWidth/2, -25);
  else enemies.emplace_back(Board::playAreaWidth - 132 - Enemy::enemyPhysicalWidth/2, -25);
  reportEnemyEnters(enemies.back());
}

