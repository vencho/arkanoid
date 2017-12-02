#include<model/Ball.h>
#include<model/Paddle.h>
#include<cstdio>
#include<cmath>

int Ball::framesLeftSlow = 0;
const double Ball::baseSpeed = 4.242640687; // 3*sqrt(2)

Ball::Ball(const Paddle &player) {
  frozen = 0;
  frozen_player = nullptr;
  frozen_partX = 0;
  frozen_offsetY = 0;
  width = ballPhysicalWidth;
  height = ballPhysicalHeight;

  setX(player.getX() + (player.getWidth() - width) / 2);
  setY(player.getY() - height);

  setAngle(-2*M_PI/5);
  stick(player, 3);
}

void Ball::setAngle(double angle) {
  double cs = cos(angle);
  double sn = sin(angle);
  scaledVx = (int) (baseSpeed * denominator * cs);
  scaledVy = (int) (baseSpeed * denominator * sn);
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

void Ball::stopSlow() {
  framesLeftSlow = 0;
}

void Ball::move() {
  if(!framesLeftSlow) MovableRectangle::move();
  else {
    scaledX += scaledVx / 2;
    scaledY += scaledVy / 2;
  }
}

void Ball::tick() {  
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
    setX(frozen_player -> getX() + (frozen_partX * frozen_player -> getWidth())/10000);
  }
}

void Ball::tickSlow() {
  if(framesLeftSlow) framesLeftSlow--;
}

// mask says which side you got stuck to: 1 for left, 2 for right, 3 for top
void Ball::stick(const Paddle &player, int mask) {
  frozen = mask;
  frozen_player = &player;
  frozen_offsetY = getY() - player.getY();;

  if(frozen == 3) {
    frozen_partX = (int) (((getX() - player.getX()) / (double) player.getWidth()) * 10000);
  }
}

void Ball::unstick() {
  frozen = false;
  frozen_player = nullptr;
  frozen_partX = 0;
  frozen_offsetY = 0;
}

void Ball::modifyAngle(const Paddle &player) {
  double ballMidx = getX() + (width - 1) / 2.;
  double f = (ballMidx - player.getX()) / player.getWidth();
  double angle;
  if(f < 0.1) angle = -5*M_PI/6;
  else if(f > 0.9) angle = -M_PI/6;
  else angle = (M_PI/6.) * (5*f - 5.5);
  setAngle(angle);
}
