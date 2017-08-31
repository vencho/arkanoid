#include<Ball.h>
#include<cstdio>

Ball::Ball(int x, int y, int dx, int dy) : MovableRectangularObject(x-BALL_R, y-BALL_R, 2*BALL_R, 2*BALL_R, dx, dy) { }

void Ball::report() {
  printf("Position (%d %d), direction (%d %d)\n", getX(), getY(), getVelocityX(), getVelocityY());
}
