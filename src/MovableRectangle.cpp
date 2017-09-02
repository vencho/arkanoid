#include<MovableRectangle.h>
#include<cstdio>

MovableRectangle::MovableRectangle(
						   int x, 
						   int y, 
						   int width, 
						   int height, 
						   int velocityX, 
						   int velocityY) : DockedRectangle(x, y, width, height) {
  this -> velocityX = velocityX;
  this -> velocityY = velocityY;
}

void MovableRectangle::move() {
  x += velocityX;
  y += velocityY;
}

void MovableRectangle::tick() {
  move();
}

int & MovableRectangle::getVelocityX() { return velocityX; }
int & MovableRectangle::getVelocityY() { return velocityY; }
void MovableRectangle::setVelocity(int dx, int dy) { setVelocityX(dx); setVelocityY(dy); }
void MovableRectangle::setVelocityX(int dx) { velocityX = dx; }
void MovableRectangle::setVelocityY(int dy) { velocityY = dy; }
