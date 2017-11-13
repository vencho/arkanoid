#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<geometry/CollisionManager.h>
#include<cstdio>
#include<string>

bool Board::gameWon() {
  return tiles.size() == 0;
}

bool Board::gameLost() {
  return balls.size() == 0;
}

void Board::collisionLogic() {
  for(int i = 0; i < balls.size(); i++) {
    for(int j = 0; j < tiles.size(); j++) {
      if(CollisionManager::collideRectangle(balls[i], tiles[j], true)) {
	tiles[j].takeDamage();
	reportTileHit(tiles[j].getId());
      }
      if(tiles[j].getHealth() == 0) {
	reportTileDestruction(tiles[j].getId());
	tiles.erase(tiles.begin() + j);
	j--;
      }
    }
  }

  for(int i = 0; i < balls.size(); i++) {
    CollisionManager::collideRectangle(balls[i], player, true);
  }

  for(int i = 0; i < balls.size(); i++) {
    CollisionManager::collideBorders(balls[i]);
  }

  CollisionManager::collideBorders(player);
}

Board::Board(int width, int height) : 
  player(width/2 - BASE_PADDLE_WIDTH/2, PADDLE_OFFSET_FROM_TOP + BASE_PADDLE_HEIGHT) {
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


void Board::addDeathMonitor(DeathMonitor *dm) {
  deathMonitors.push_back(dm);
}


void Board::addTileDestructionMonitor(TileDestructionMonitor *tdm) {
  tileDestructionMonitors.push_back(tdm);
}

void Board::reportDeath() {
  for(int i = 0; i < deathMonitors.size(); i++) {
    deathMonitors[i] -> notifyDied();
  }
}

void Board::reportTileHit(int id) {
  for(int i = 0; i < tileDestructionMonitors.size(); i++) {
    tileDestructionMonitors[i] -> notifyTileHit(id);
  }
}

void Board::reportTileDestruction(int id) {
  for(int i = 0; i < tileDestructionMonitors.size(); i++) {
    tileDestructionMonitors[i] -> notifyTileDestroyed(id);
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
}

Ball & Board::getBall(int num) {
  return balls[num];
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
