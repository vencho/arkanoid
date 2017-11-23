#include<model/Paddle.h>

Paddle::Paddle(int x, int y) : MovableRectangle(x, y, BASE_PADDLE_WIDTH, BASE_PADDLE_HEIGHT) {
  whichPaddleLength = 0;
  ticksLeftLaser = 0;
  ticksLeftEnlarge = 0;
  ticksLeftCatch = 0;
}

const int Paddle::paddleLength[8] = { 80, 92, 100, 108, 116, 120, 124, 128 };

void Paddle::setLength(int newSpriteNumber) {
  int oldLength = paddleLength[whichPaddleLength];
  int newLength = paddleLength[newSpriteNumber];
  int oldx = getX();
  int newx = oldx - (newLength - oldLength) / 2;
  whichPaddleLength = newSpriteNumber;
  width = paddleLength[whichPaddleLength];
  setX(newx);
}

void Paddle::tick() {
  MovableRectangle::tick();
  if(ticksLeftLaser) ticksLeftLaser--;
  if(ticksLeftCatch) ticksLeftCatch--;

  if(ticksLeftEnlarge) ticksLeftEnlarge--;
  if( (Configuration::powerupDuration - ticksLeftEnlarge) % 3 == 0 ) {
    int newLength = (Configuration::powerupDuration - ticksLeftEnlarge) / 3;
    if( newLength < 8 && newLength > whichPaddleLength) {
      setLength(newLength);
    }
  }
  if(ticksLeftEnlarge == 0) setLength(0);
}

int Paddle::getLength() {
  return whichPaddleLength;
}

void Paddle::startEnlarge() {
  ticksLeftEnlarge = Configuration::powerupDuration;
}

void Paddle::startCatch() {
  ticksLeftCatch = Configuration::powerupDuration;
}

bool Paddle::catchActive() {
  return (ticksLeftCatch > 0);
}
