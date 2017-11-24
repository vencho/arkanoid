#ifndef MOVRECT_H_DEFINED
#define MOVRECT_H_DEFINED
#include<geometry/DockedRectangle.h>
#include<cmath>

class MovableRectangle : public DockedRectangle {
 protected:
  /*
    The velocity is (scaledVx, scaledVy) / denominator.
  */
  int scaledVx, scaledVy;
  virtual void move();
  double getScaledSpeed();
  void setAngle(double newangle);

 public:
  MovableRectangle(int x, int y, int width, int height, int velocityX = 0, int velocityY = 0);
  int getPreviousY();
  int getPreviousX();
  int getVelocityX();
  int getVelocityY();
  void setVelocity(int dx, int dy);
  void setVelocityX(int dx);
  void setVelocityY(int dy);
  void tick();
  bool isMoving();
  bool isMovingX();
  bool isMovingY();
  bool isMovingX(bool small);
  bool isMovingY(bool small);
  void reflectOrthogonally(bool verticalLine);
};

#endif
