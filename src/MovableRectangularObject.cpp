#include<MovableRectangularObject.h>
#include<cstdio>

MovableRectangularObject::MovableRectangularObject(
						   int x, 
						   int y, 
						   int width, 
						   int height, 
						   int velocityX, 
						   int velocityY) : RectangularObject(x, y, width, height) {
  this -> velocityX = velocityX;
  this -> velocityY = velocityY;
}

void MovableRectangularObject::move() {
  x += velocityX;
  y += velocityY;
}

void MovableRectangularObject::tick() {
  move();
}

int MovableRectangularObject::getVelocityX() { return velocityX; }
int MovableRectangularObject::getVelocityY() { return velocityY; }

void MovableRectangularObject::setVelocity(int dx, int dy) { setVelocityX(dx); setVelocityY(dy); }
void MovableRectangularObject::setVelocityX(int dx) { velocityX = dx; }
void MovableRectangularObject::setVelocityY(int dy) { velocityY = dy; }
