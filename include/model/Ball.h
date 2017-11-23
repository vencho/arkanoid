#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include<model/Tile.h>
#include<model/Paddle.h>
#include<geometry/MovableRectangle.h>

class Ball : public MovableRectangle {
 public:
  Ball(int x, int y, int dx, int dy);
  void modifyAngle(Paddle &player);
  virtual void tick();
  virtual void move();
  void stick(Paddle &player, int stickCode);
  void unstick();
  static void startSlow();
 private:
  static int framesLeftSlow;
  int frozen;
  Paddle *frozen_player;
  int frozen_offsetY;
  int frozen_partX; // out of 1000
};

#endif
