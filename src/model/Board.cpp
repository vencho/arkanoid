#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<model/Powerup.h>
#include<geometry/CollisionManager.h>
#include<cstdio>
#include<string>

Board::EnemySpawner::EnemySpawner(Board &board) : board(board) {
  ticksSinceSpawnLeft = 0;
  ticksSinceSpawnRight = 400;
  spawnRate = 800;
}

void Board::EnemySpawner::tick() {
  ticksSinceSpawnLeft++;
  ticksSinceSpawnRight++;

  if(ticksSinceSpawnLeft == spawnRate) {
    ticksSinceSpawnLeft = 0;
    board.spawnEnemy(true);
  }
  if(ticksSinceSpawnRight == spawnRate) {
    ticksSinceSpawnRight = 0;
    board.spawnEnemy(false);
  }
}

void Board::fireBullets() {
  if(!player.canFire()) return;
  bullets.emplace_back(player, true);
  bullets.emplace_back(player, false);
  player.fire();
}

void Board::collideBulletsWithEnemies() {
  for(int i = 0; i < bullets.size(); i++) {
    bool killBullet = false;
    for(int j = 0; j < enemies.size(); j++) {
      if(CollisionManager::rectanglesIntersect(bullets[i], enemies[j])) {
	reportEnemyDestroyed(enemies[j]);
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
      reportTileHit(tile.getId());
      printf("Tile with id %d takes damage, health down to %d.\n", tile.getId(), tile.getHealth());
      if(tile.getHealth() == 0) {
	destroyTile(j);
	j--;
      }
    }
    if(hitSomething) {
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
      reportTileHit(tile.getId());
      printf("Tile with id %d takes damage, health down to %d.\n", tile.getId(), tile.getHealth());
      if(tile.getHealth() == 0) {
	destroyTile(whichTilesHit[j] - countRemoved);
	countRemoved++;
      }
    }
  }
}

void Board::collidePlayerWithEnemies() {
  for(int i = 0; i < enemies.size(); i++) {
    if(CollisionManager::rectanglesIntersect(player, enemies[i])) {
      reportEnemyDestroyed(enemies[i]);
      enemies.erase(enemies.begin() + i);
      i--;
    }
  }
}

void Board::collideBallsWithEnemies() {
  for(int i = 0; i < balls.size(); i++) {
    for(int j = 0; j < enemies.size(); j++) {
      if(CollisionManager::collideRectangle(balls[i], enemies[j], 15, 3)) {
	reportEnemyDestroyed(enemies[j]);
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
      reportPowerupDestroyed(powerups[i].getId());
      powerups.erase(powerups.begin() + i);
      i--;
    }
  }
}

void Board::startDisruption() {
  int n = balls.size();
  for(int i = 0; i < n; i++) {
    balls.push_back(balls[i]);
    balls.back().modifyAngle(M_PI/6);
    balls.push_back(balls[i]);
    balls.back().modifyAngle(-M_PI/6);
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

void Board::destroyTile(int idx) {
  printf("Erasing tile with id %d.\n", tiles[idx].getId());
  reportTileDestruction(tiles[idx].getId());
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
  powerups.emplace_back(tiles[idx], powerupLetter);
  tiles.erase(tiles.begin() + idx);
}

Board::Board() : enemySpawner(*this) {
}

void Board::resetBoard(std::string filename) {
  enemies.clear();
  powerups.clear();
  bullets.clear();

  balls.clear();
  balls.emplace_back(player);
  Ball::stopSlow();

  loadTiles(filename);

  player.reset();

  // FIXME: reset enemy spawner and powerup spawner
}

void Board::loadTiles(std::string filename) {
  tiles.clear();
  FILE *fin = fopen(filename.c_str(), "r");
  int row, column, health, colour;
  while(1) {
    if(fscanf(fin, "%d%d%d%d", &row, &column, &health, &colour) != 4) break;
    tiles.emplace_back(row, column, health, colour);
  }
  fclose(fin);
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

void Board::reportTileHit(int id) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyTileHit(id);
  }
}

void Board::reportTileDestruction(int id) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyTileDestroyed(id);
  }
}

void Board::reportPowerupDestroyed(int id) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyPowerupDestroyed(id);
  }
}

void Board::reportEnemyDestroyed(Enemy &enemy) const {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyEnemyDestroyed(enemy);
  }
}

void Board::tick() {
  static int timetorespawn = -1;
  if(balls.empty()) {
    if(timetorespawn > 0) timetorespawn--;
    else if(timetorespawn == 0) {
      reportDeath();
      balls.emplace_back(player);
      timetorespawn--;
    }
    else {
      timetorespawn = respawnTimeInFrames;
    }
  }
  
  enemySpawner.tick();

  player.tick();
  collidePlayerWithBorders();
  for(int i = 0; i < balls.size(); i++) {
    balls[i].tick();
    if(balls[i].getY() > playAreaHeight) {
      balls[i] = balls.back();
      balls.pop_back();
      i--;
    }
  }
  Ball::tickSlow();
  
  for(int i = 0; i < bullets.size(); i++) {
    bullets[i].tick();
    if(CollisionManager::collideBorders(bullets[i])) {
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
      reportPowerupDestroyed(powerups[i].getId());
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

void Board::spawnEnemy(bool left) {
  if(left) enemies.emplace_back(90, 0);
  else enemies.emplace_back(270, 0);
}
