#include<RectangularObject.h>

#ifndef MOVRECTOBJ_H_DEFINED
#define MOVRECTOBJ_H_DEFINED

class MovableRectangularObject : public RectangularObject {
 protected:
  int velocityX, velocityY;
  void move();
 public:
  MovableRectangularObject(int x, int y, int width, int height, int velocityX = 0, int velocityY = 0);
  int getVelocityX();
  int getVelocityY();
  void setVelocity(int dx, int dy);
  void setVelocityX(int dx);
  void setVelocityY(int dy);
  void tick();
};

#endif
