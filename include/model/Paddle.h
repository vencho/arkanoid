#include<Global.h>
#include<geometry/MovableRectangle.h>

#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
class Paddle : public MovableRectangle {
 public:
  Paddle(int x, int y);
};

#endif
