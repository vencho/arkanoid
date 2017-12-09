#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include<model/GameObject.h>
#include<geometry/MovableRectangle.h>
class Tile;

class Powerup : public MovableRectangle, public GameObject {
 private:
  char type;
 public:
  const static int powerupPhysicalWidth = 44;
  const static int powerupPhysicalHeight = 22;
  char getType() const;
  Powerup(const Tile &tile, char type);
};

#endif
