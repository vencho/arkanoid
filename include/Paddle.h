#include<Global.h>

#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
class Paddle {
 private:
  // coordinates of upper left corner
  int x, y;
  // velocity
  int dx, dy;
  // width and height
  int width, height;
  void move();
  
 public:
  Paddle(int x, int y);
  void tick();
  void alterVelocity(int dx, int dy);
  int getX();
  int getY();
  int getWidth();
  int getHeight();
};

#endif
