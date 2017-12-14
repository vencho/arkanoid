#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include<geometry/DockedRectangle.h>
#include<model/GameObject.h>

class Tile : public DockedRectangle, public GameObject {
 private:
  // zero means the tile should disappear
  int healthleft;
  // true if tile takes no damage
  bool indestructible;
  int colour;
  int id;
 public: 
  const static int tilePhysicalWidth = 44;
  const static int tilePhysicalHeight = 22;
  void takeDamage();
  Tile(int x, int y, int colour);
  int getColour() const;
  // int getId() const;
  int getHealth() const;
};

#endif
