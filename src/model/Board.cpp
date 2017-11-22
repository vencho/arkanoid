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


void Board::collideBallsWithBorders() {
  for(int i = 0; i < balls.size(); i++) {
    CollisionManager::collideBorders(balls[i]);
  }
}

void Board::collideBallsWithPlayer() {
  for(int i = 0; i < balls.size(); i++) {
    int answerMask = CollisionManager::collideRectangle(balls[i], player, true);
    if((answerMask & 1) || (answerMask & 4) || (answerMask & 8) ) balls[i].modifyAngle(player);
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
	CollisionManager::collideRectangle(balls[i], tile, true);
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
      CollisionManager::collideRectangle(balls[i], rect, true);
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

void Board::consumePowerup(Powerup &powerup) {
  printf("Consumed powerup with id %d of type %c.\n", powerup.getId(), powerup.getType());
  if(powerup.getType() == 'E') player.startEnlarge();
}

Board::Board(int width, int height) : 
  player(56/*width/2 - BASE_PADDLE_WIDTH/2*/, PADDLE_OFFSET_FROM_TOP + BASE_PADDLE_HEIGHT) {
  this -> width = width;
  this -> height = height;
}

void Board::resetBoard(std::string filename) {
  balls.clear();
  balls.push_back(Ball(0, 0, 0, 0));
  balls[0].snapToPaddle(player);

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

void Board::initialiseBalls() {
  for(int i = 0; i < balls.size(); i++) {
    if(!balls[i].isInitialised()) {
      balls[i].initialise();
    }
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
      Ball b(0, 0, 0, 0);
      b.snapToPaddle(player);
      balls.push_back(b);
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

  collisionLogic();

  for(int i = 0; i < balls.size(); i++) {
    if(!balls[i].isInitialised()) {
      balls[i].snapToPaddle(player); 
    }
  }

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
