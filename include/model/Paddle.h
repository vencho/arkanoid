#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include<Global.h>
#include<geometry/MovableRectangle.h>
#include<Configuration.h>
#include<model/Tile.h>

class Paddle : public MovableRectangle {
 private:
  int ticksLeftLaser;
  int ticksLeftEnlarge;
  int ticksLeftCatch;
  int laserCooldown;

  // 0 to 7 smallest to largest.
  int whichPaddleLength; 


 public:

  const static int paddleOffsetFromTop = 26*Tile::tilePhysicalHeight;
  const static int paddlePhysicalHeight = Tile::tilePhysicalHeight;
  const static int paddlePhysicalLength[8];
  const static int paddleSpeedWhenMoving = 5;

  Paddle();
  int getLength() const;
  bool canFire() const;
  bool laserActive() const;
  bool catchActive() const;
  void setLength(int newSpriteNumber);
  void startCatch();
  void startEnlarge();
  void startLaser();
  void fire();
  void tick();
  void reset();
};

#endif
