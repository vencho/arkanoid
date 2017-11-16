#include<model/Ball.h>
#include<cstdio>

Ball::Ball(int x, int y, int dx, int dy) : MovableRectangle(x, y, BALL_WIDTH, BALL_HEIGHT, dx, dy) { }

void Ball::snapToPaddle(Paddle &player) {
  setX(player.getX() + player.getWidth()/2);
  setY(player.getY() - BALL_HEIGHT);
  scaledVx = scaledVy = 0;
}

bool Ball::isInitialised() {
  return isMoving();
}

void Ball::initialise() {
  scaledVx = denominator * BALL_SPEED_X;
  scaledVy = -denominator * BALL_SPEED_Y;
}
