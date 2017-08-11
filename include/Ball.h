#include<Tile.h>
#include<Paddle.h>

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#define BALL_R 5

class Ball {
 private:
  int x, y, dx, dy;
  bool collideSegment(int val, bool vertical, bool smallsidesolid, int vlow, int vhigh);
  bool collideLine(int val, bool vertical, bool smallsidesolid);
  void move();

 public:
  int getX();
  int getY();
  void tick();
  void collide(Tile &tile);
  void collide(Paddle &player);
  void collideBorders();
  Ball(int x, int y, int dx, int dy);
  void report();
};

#endif
