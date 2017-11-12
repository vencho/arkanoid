#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include<Global.h>
#include<geometry/DockedRectangle.h>

class Tile : public DockedRectangle {
 private:
  // zero means the tile should disappear
  int healthleft;
  // true if tile takes no damage
  bool indestructible;

 public: 
  int getHealth();
  void takeDamage();
  Tile(int x, int y, int healthleft);
};

#endif
