#include<Board.h>
#include<Ball.h>
#include<Paddle.h>
#include<cstdio>
#include<CollisionManager.h>

bool Board::gameWon() {
  return tiles.size() == 0;
}

bool Board::gameLost() {
  return balls.size() == 0;
}

void Board::collisionLogic() {
  for(int i = 0; i < balls.size(); i++) {
    for(int j = 0; j < tiles.size(); j++) {
      if(CollisionManager::collideRectangle(balls[i], tiles[j], true)) tiles[j].takeDamage();

      if(tiles[j].getHealth() == 0) {
	printf("Tile removed.\n");
	tiles[j] = tiles.back();
	tiles.pop_back();
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

  balls.push_back(Ball(0, 0, 0, 0));
  balls[0].snapToPaddle(player);

  tiles.push_back(Tile(4, 1, 2));
  tiles.push_back(Tile(4, 3, 2));
  tiles.push_back(Tile(4, 5, 2));
  tiles.push_back(Tile(4, 7, 2));
}

void Board::initialiseBalls() {
  for(int i = 0; i < balls.size(); i++) {
    if(!balls[i].isInitialised()) {
      balls[i].initialise();
    }
  }
}

void Board::tick() {
  static int timetorespawn = -1;
  if(balls.empty()) {
    if(timetorespawn > 0) timetorespawn--;
    else if(timetorespawn == 0) {
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
    if(!balls[i].isInitialised()) balls[i].snapToPaddle(player); 
    if(balls[i].getY() > MAXY) {
      balls[i] = balls.back();
      balls.pop_back();
      i--;
    }
  }
  collisionLogic();
}

void Board::report() {
  for(int i = 0; i < balls.size(); i++) {
    balls[i].report();
  }
}


Ball & Board::getBall(int num) {
  return balls[num];
}

int Board::numTiles() {
  return tiles.size();
}

Tile & Board::getTile(int i) {
  return tiles[i];
}

Paddle & Board::getPaddle() {
  return player;
}
