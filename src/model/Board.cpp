#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<model/Powerup.h>
#include<geometry/CollisionManager.h>
#include<cstdio>
#include<string>

bool Board::gameWon() {
  return tiles.size() == 0;
}

bool Board::gameLost() {
  return balls.size() == 0;
}

void Board::fireBullets() {
  if(!player.canFire()) return;
  bullets.emplace_back(player, true);
  bullets.emplace_back(player, false);
  player.fire();
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
	reportTileDestruction(tile.getId());
	tiles.erase(tiles.begin() + j);
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
	reportTileDestruction(tile.getId());

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
	powerups.emplace_back(tile, powerupLetter);

	printf("Erasing tile with id %d.\n", tile.getId());
	tiles.erase(tiles.begin() + whichTilesHit[j] - countRemoved);
	countRemoved++;
      }
    }
  }
}

void Board::collisionLogic() {
  collideBulletsWithTiles();
  collideBallsWithTiles();
  collideBallsWithPlayer();
  collideBallsWithBorders();
  collidePlayerWithBorders();
  collidePlayerWithPowerups();
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

void Board::disruptionPowerup() {
  int n = balls.size();
  for(int i = 0; i < n; i++) {
    balls.push_back(balls[i]);
    balls.back().modifyAngle(M_PI/6);
    balls.push_back(balls[i]);
    balls.back().modifyAngle(-M_PI/6);
  }
}

void Board::consumePowerup(Powerup &powerup) {
  printf("Consumed powerup with id %d of type %c.\n", powerup.getId(), powerup.getType());
  if(powerup.getType() == 'E') player.startEnlarge();
  else if(powerup.getType() == 'C') player.startCatch();
  else if(powerup.getType() == 'S') Ball::startSlow();
  else if(powerup.getType() == 'D') disruptionPowerup();
  else if(powerup.getType() == 'L') player.startLaser();
}

Board::Board(int width, int height) : 
  player(45/*width/2 - BASE_PADDLE_WIDTH/2*/, PADDLE_OFFSET_FROM_TOP + BASE_PADDLE_HEIGHT) {
  this -> width = width;
  this -> height = height;
}

void Board::resetBoard(std::string filename) {
  balls.clear();
  balls.push_back(Ball(0, 0));
  balls.back().setX(player.getX() + player.getWidth()/2);
  balls.back().setY(player.getY() - BALL_HEIGHT);
  balls.back().stick(player, 3);
  loadTiles(filename);
}

void Board::loadTiles(std::string filename) {
  tiles.clear();
  FILE *fin = fopen(filename.c_str(), "r");
  int row, column, health, colour;
  while(1) {
    if(fscanf(fin, "%d%d%d%d", &row, &column, &health, &colour) != 4) break;
    tiles.push_back(Tile(row, column, health, colour));
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

void Board::reportDeath() {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyDied();
  }
}

void Board::reportTileHit(int id) {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyTileHit(id);
  }
}

void Board::reportTileDestruction(int id) {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyTileDestroyed(id);
  }
}

void Board::reportPowerupDestroyed(int id) {
  for(int i = 0; i < monitors.size(); i++) {
    monitors[i] -> notifyPowerupDestroyed(id);
  }
}

void Board::tick() {
  static int timetorespawn = -1;
  if(balls.empty()) {
    if(timetorespawn > 0) timetorespawn--;
    else if(timetorespawn == 0) {
      reportDeath();
      balls.push_back(Ball(0, 0));
      balls.back().setX(player.getX() + player.getWidth()/2);
      balls.back().setY(player.getY() - BALL_HEIGHT);
      balls.back().stick(player, 3);
      timetorespawn--;
    }
    else {
      timetorespawn = RESPAWN_TIME_IN_FRAMES;
    }
  }
  
  player.tick();
  for(int i = 0; i < balls.size(); i++) {
    balls[i].tick();
    if(balls[i].getY() > GAME_SCREEN_HEIGHT) {
      balls[i] = balls.back();
      balls.pop_back();
      i--;
    }
  }

  for(int i = 0; i < bullets.size(); i++) {
    bullets[i].tick();
    if(CollisionManager::collideBorders(bullets[i])) {
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }

  collisionLogic();

  for(int i = 0; i < powerups.size(); i++) {
    powerups[i].tick();
    if(powerups[i].getY() > GAME_SCREEN_HEIGHT) {
      printf("Powerup with id %d and type %c has left the screen.\n", powerups[i].getId(), powerups[i].getType());
      reportPowerupDestroyed(powerups[i].getId());
      powerups.erase(powerups.begin() + i);
      i--;
    }
  }
}


std::vector<Ball> &Board::getBalls() {
  return balls;
}

std::vector<Bullet> &Board::getBullets() {
  return bullets;
}

int Board::numTiles() {
  return tiles.size();
}

int Board::numBalls() {
  return balls.size();
}

Tile & Board::getTile(int i) {
  return tiles[i];
}

std::vector<Tile> & Board::getTiles() {
  return tiles;
}

Paddle & Board::getPaddle() {
  return player;
}

std::vector<Powerup> &Board::getPowerups() {
  return powerups;
}
