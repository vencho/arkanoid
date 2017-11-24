#include<Global.h>
#include<geometry/MovableRectangle.h>
#include<Configuration.h>

#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
class Paddle : public MovableRectangle {
  int ticksLeftLaser;
  int ticksLeftEnlarge;
  int ticksLeftCatch;
  int laserCooldown;

  // 0 to 7 corresponding to 
  // sprites from smallest to largest.
  int whichPaddleLength; 

  const static int paddleLength[8];

 public:
  Paddle(int x, int y);
  void tick();
  void startEnlarge();
  int getLength();
  void setLength(int newSpriteNumber);
  void startCatch();
  void startLaser();
  bool catchActive();
  void fire();
  bool canFire();
  bool laserActive();
};

#endif
