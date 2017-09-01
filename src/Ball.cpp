#include<Ball.h>
#include<cstdio>

Ball::Ball(int x, int y, int dx, int dy) : MovableRectangularObject(x, y, BALL_WIDTH, BALL_HEIGHT, dx, dy) { }

void Ball::snapToPaddle(Paddle &player) {
  x = player.getX() + player.getWidth()/2;
  y = player.getY() - BALL_HEIGHT;
  velocityX = velocityY = 0;
}

void Ball::report() {
  printf("Position (%d %d), direction (%d %d)\n", getX(), getY(), getVelocityX(), getVelocityY());
}

bool Ball::isInitialised() {
  return velocityX || velocityY;
}

void Ball::initialise() {
  velocityX = BALL_SPEED_X;
  velocityY = -BALL_SPEED_Y;
}
