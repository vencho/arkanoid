#include<Tile.h>
#include<Paddle.h>
#include<MovableRectangularObject.h>

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

class Ball : public MovableRectangularObject {
 public:
  Ball(int x, int y, int dx, int dy);
  void report();
  bool isInitialised();
  void initialise();
  void snapToPaddle(Paddle &player);
};

#endif
