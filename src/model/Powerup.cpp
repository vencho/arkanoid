#include<model/Powerup.h>
#include<model/Tile.h>

char Powerup::getType() const {
  return type;
}

int Powerup::getId() const {
  return id;
}

Powerup::Powerup(const Tile &tile, char type) : MovableRectangle(tile.getX(), tile.getY(), POWERUP_WIDTH, POWERUP_HEIGHT, 0, 1) {
  static int nextIdToAssign = 0;
  this -> type = type;
  this -> id = nextIdToAssign++;
}
