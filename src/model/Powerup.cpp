#include<model/Powerup.h>
#include<model/Tile.h>

char Powerup::getType() {
  return type;
}

int Powerup::getId() {
  return id;
}

Powerup::Powerup(Tile &tile, char type) : MovableRectangle(tile.getX(), tile.getY(), POWERUP_WIDTH, POWERUP_HEIGHT, 0, 1) {
  static int nextIdToAssign = 0;
  this -> type = type;
  this -> id = nextIdToAssign++;
}
