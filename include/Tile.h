#include<Global.h>

#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class Tile {
 private:
  // zero means the tile should disappear
  int healthleft;

  // true if tile takes no damage
  bool indestructible;

  // coordinates of upper-left corner
  int x, y; 

 public: 
  int getX();
  int getY();
  int getHealth();
  void takeDamage();
  Tile(int x, int y, int healthleft);
};

#endif
