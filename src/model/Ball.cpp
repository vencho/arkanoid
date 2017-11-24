#include<model/Ball.h>
#include<model/Paddle.h>
#include<cstdio>
#include<cmath>

int Ball::framesLeftSlow = 0;

Ball::Ball(int x, int y, int dx, int dy) : MovableRectangle(x, y, BALL_WIDTH, BALL_HEIGHT, dx, dy) { 
  frozen = 0;
  frozen_player = nullptr;
  frozen_partX = 0;
  frozen_offsetY = 0;
}

void Ball::modifyAngle(double angle) {
  double cs = cos(angle);
  double sn = sin(angle);
  scaledVx = (int) (cs * scaledVx - sn * scaledVy);
  scaledVy = (int) (sn * scaledVx + cs * scaledVy);
}

void Ball::startSlow() {
  framesLeftSlow = Configuration::powerupDuration;
}

void Ball::move() {
  if(!framesLeftSlow) MovableRectangle::move();
  else {
    scaledX += scaledVx / 2;
    scaledY += scaledVy / 2;
  }
}

void Ball::tick() {
  if(framesLeftSlow) framesLeftSlow--;
  
  if(!frozen) {
    move();
    return;
  }

  setY(frozen_player -> getY() + frozen_offsetY);

  if(frozen == 1) {
    setX(frozen_player -> getX() - getWidth()); 
  }
  else if(frozen == 2) {
    setX(frozen_player -> getX() + frozen_player -> getWidth()); 
  }
  else {
    setX(frozen_player -> getX() + (frozen_partX * frozen_player -> getWidth())/1000);
  }
}

// mask says which side you got stuck to: 1 for left, 2 for right, 3 for top
void Ball::stick(Paddle &player, int mask) {
  frozen = mask;
  frozen_player = &player;
  frozen_offsetY = getY() - player.getY();;

  if(frozen == 3) {
    frozen_partX = (int) (((getX() - player.getX()) / (double) player.getWidth()) * 1000);
  }
}

void Ball::unstick() {
  frozen = false;
  frozen_player = nullptr;
  frozen_partX = 0;
  frozen_offsetY = 0;
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
