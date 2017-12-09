#ifndef BULLET_H_DEFINED
#define BULLET_H_DEFINED

#include<geometry/MovableRectangle.h>
#include<model/Paddle.h>

class Bullet : public MovableRectangle, public GameObject {
 public:
  Bullet(const Paddle &player, bool leftside);
};

#endif
