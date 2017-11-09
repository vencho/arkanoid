#include<model/Tile.h>

bool Tile::operator<(const Tile &other) {
  if(x != other.x) return x < other.x;
  return y < other.y;
}

Tile::Tile(int i, int j, int healthleft) : DockedRectangle( (j-1)*TILE_WIDTH, (i-1)*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT ) {
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
