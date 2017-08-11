#include<Tile.h>
#include<Paddle.h>
#include<MovableRectangularObject.h>

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

class Ball : public MovableRectangularObject {
 private:
  bool collideSegment(int val, bool vertical, bool smallsidesolid, int vlow, int vhigh);
  bool collideLine(int val, bool vertical, bool smallsidesolid);

 public:
  Ball(int x, int y, int dx, int dy);
  void collide(Tile &tile);
  void collide(Paddle &player);
  void collideBorders();
  void report();
};

#endif
