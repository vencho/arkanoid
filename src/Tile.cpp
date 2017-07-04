#include<Tile.h>

Tile::Tile(int i, int j, int healthleft) {
  this -> x = (j-1)*TILE_WIDTH;
  this -> y = (i-1)*TILE_HEIGHT;
  this -> healthleft = healthleft;
  this -> indestructible = false;
}

int Tile::getX() {
  return x;
}

int Tile::getY() {
  return y;
}

int Tile::getHealth() {
  return healthleft;
}

void Tile::takeDamage() {
  if(!indestructible) {
    healthleft--;
  }
}
