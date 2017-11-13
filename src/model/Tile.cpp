#include<model/Tile.h>

Tile::Tile(int i, int j, int healthleft, int colour) : DockedRectangle( (j-1)*TILE_WIDTH, (i-1)*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT ) {
  static int nextIdToAssign = 7;
  this -> healthleft = healthleft;
  this -> indestructible = false;
  this -> colour = colour;
  this -> id = nextIdToAssign++;
}

int Tile::getId() {
  return id;
}

int Tile::getColour() {
  return colour;
}

int Tile::getHealth() {
  return healthleft;
}

void Tile::takeDamage() {
  if(!indestructible) {
    healthleft--;
  }
}
