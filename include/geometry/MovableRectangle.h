#ifndef MOVRECT_H_DEFINED
#define MOVRECT_H_DEFINED
#include<geometry/DockedRectangle.h>

class MovableRectangle : public DockedRectangle {
 protected:
  int velocityX, velocityY;
  void move();
 public:
  MovableRectangle(int x, int y, int width, int height, int velocityX = 0, int velocityY = 0);
  int getVelocityX();
  int getVelocityY();
  void setVelocity(int dx, int dy);
  void setVelocityX(int dx);
  void setVelocityY(int dy);
  void tick();
};

#endif
