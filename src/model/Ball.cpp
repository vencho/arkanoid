#include<model/Ball.h>
#include<model/Paddle.h>
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

void Ball::modifyAngle(Paddle &player) {
  double ballMidx = getX() + (width - 1) / 2.;
  double f = (ballMidx - player.getX()) / player.getWidth();
  double angle;
  if(f < 0.1) angle = -5*M_PI/6;
  else if(f > 0.9) angle = -M_PI/6;
  else angle = (M_PI/6.) * (5*f - 5.5);
  setAngle(angle);
}
