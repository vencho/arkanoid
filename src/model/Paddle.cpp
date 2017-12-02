#include<model/Paddle.h>
#include<model/Board.h>

const int Paddle::paddlePhysicalLength[8] = { 80, 92, 100, 108, 116, 120, 124, 128 };

Paddle::Paddle() : MovableRectangle(0, 0, paddlePhysicalLength[0], paddlePhysicalHeight) {
  reset();
}

void Paddle::reset() {
  setX( (Board::playAreaWidth - width) / 2 );
  setY(paddleOffsetFromTop);
  whichPaddleLength = 0;
  ticksLeftLaser = 0;
  ticksLeftEnlarge = 0;
  ticksLeftCatch = 0;
  laserCooldown = 0;
}

void Paddle::setLength(int newSpriteNumber) {
  int oldLength = paddlePhysicalLength[whichPaddleLength];
  int newLength = paddlePhysicalLength[newSpriteNumber];
  int oldx = getX();
  int newx = oldx - (newLength - oldLength) / 2;
  whichPaddleLength = newSpriteNumber;
  width = paddlePhysicalLength[whichPaddleLength];
  setX(newx);
}

void Paddle::tick() {
  MovableRectangle::tick();
  if(ticksLeftLaser) ticksLeftLaser--;
  if(ticksLeftCatch) ticksLeftCatch--;

  if(laserCooldown) laserCooldown--;
  if(ticksLeftEnlarge) ticksLeftEnlarge--;
  if( (Configuration::powerupDuration - ticksLeftEnlarge) % 3 == 0 ) {
    int newLength = (Configuration::powerupDuration - ticksLeftEnlarge) / 3;
    if( newLength < 8 && newLength > whichPaddleLength) {
      setLength(newLength);
    }
  }
  if(ticksLeftEnlarge == 0) setLength(0);
}

int Paddle::getLength() const {
  return whichPaddleLength;
}

void Paddle::startEnlarge() {
  ticksLeftEnlarge = Configuration::powerupDuration;
}

void Paddle::startCatch() {
  ticksLeftCatch = Configuration::powerupDuration;
}

void Paddle::startLaser() {
  ticksLeftLaser = Configuration::powerupDuration;
  laserCooldown = 0;
}

bool Paddle::catchActive() const {
  return (ticksLeftCatch > 0);
}

bool Paddle::laserActive() const {
  return (ticksLeftLaser > 0);
}

bool Paddle::canFire() const {
  return laserActive() && laserCooldown == 0;
}

void Paddle::fire() {
  laserCooldown = Configuration::laserCooldown;
}
