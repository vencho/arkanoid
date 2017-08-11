#include<Tile.h>

Tile::Tile(int i, int j, int healthleft) : RectangularObject( (j-1)*TILE_WIDTH, (i-1)*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT ) {
  this -> healthleft = healthleft;
  this -> indestructible = false;
}

int Tile::getHealth() {
  return healthleft;
}

void Tile::takeDamage() {
  if(!indestructible) {
    healthleft--;
  }
}
