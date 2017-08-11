#include<Global.h>
#include<MovableRectangularObject.h>

#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
class Paddle : public MovableRectangularObject {
 public:
  Paddle(int x, int y);
};

#endif
