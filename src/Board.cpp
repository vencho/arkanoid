#include<Board.h>
#include<Ball.h>

bool Board::gameWon() {
  return tiles.size() == 0;
}

bool Board::gameLost() {
  return balls.size() == 0;
}

void Board::collisionLogic() {
  for(int i = 0; i < balls.size(); i++) {
    for(int j = 0; j < tiles.size(); j++) {
      balls[i].collide(tiles[j]);
      if(tiles[j].getHealth() == 0) {
	tiles[j] = tiles.back();
	tiles.pop_back();
	j--;
      }
    }
  }

  for(int i = 0; i < balls.size(); i++) {
    balls[i].collide(player);
  }

  for(int i = 0; i < balls.size(); i++) {
    balls[i].collideBorders();
  }
}

Board::Board(int width, int height) {
  this -> width = width;
  this -> height = height;
  balls.push_back(Ball(width/2, height/2, 3, 3));
}

void Board::tick() {
  for(int i = 0; i < balls.size(); i++) {
    balls[i].tick();
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
