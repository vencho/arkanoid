#include<model/Tile.h>

Tile::Tile(int i, int j, int healthleft, int colour) : DockedRectangle( (j-1)*tilePhysicalWidth, (i-1)*tilePhysicalHeight, 
									tilePhysicalWidth, 
									tilePhysicalHeight) {
  static int nextIdToAssign = 7;
  this -> healthleft = healthleft;
  this -> indestructible = false;
  this -> colour = colour;
  this -> id = nextIdToAssign++;
}

int Tile::getId() const {
  return id;
}

int Tile::getColour() const {
  return colour;
}

int Tile::getHealth() const {
  return healthleft;
}

void Tile::takeDamage() {
  if(!indestructible) {
    healthleft--;
  }
}
