#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include<model/Tile.h>
#include<model/Paddle.h>
#include<geometry/MovableRectangle.h>

class Ball : public MovableRectangle {
 public:
  Ball(int x, int y, int dx, int dy);
  bool isInitialised();
  void initialise();
  void snapToPaddle(Paddle &player);
};

#endif
