#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include<geometry/MovableRectangle.h>
class Tile;

class Powerup : public MovableRectangle {
 private:
  char type;
  int id;
 public:
  int getId();
  char getType();
  Powerup(Tile &tile, char type);
};

#endif
