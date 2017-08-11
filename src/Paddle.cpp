#include<Paddle.h>

int Paddle::getX() {
  return x;
}

int Paddle::getY() {
  return y;
}

int Paddle::getWidth() {
  return width;
}

int Paddle::getHeight() {
  return height;
}

Paddle::Paddle(int x, int y) {
  this -> x = x;
  this -> y = y;
  dx = 0;
  dy = 0;
  height = BASE_PADDLE_HEIGHT;
  width = BASE_PADDLE_WIDTH;
}

void Paddle::tick() {
  move();
}

void Paddle::move() {
  x += dx;
  y += dy;
}

void Paddle::alterVelocity(int dx, int dy) {
  this -> dx += dx;
  this -> dy += dy;
}
