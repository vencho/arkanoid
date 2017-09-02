#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include<Tile.h>
#include<Paddle.h>
#include<MovableRectangle.h>

class Ball : public MovableRectangle {
 public:
  Ball(int x, int y, int dx, int dy);
  bool isInitialised();
  void initialise();
  void snapToPaddle(Paddle &player);
};

#endif
