#include<RectangularObject.h>

RectangularObject::RectangularObject(int x, int y, int width, int height) {
  this -> x = x;
  this -> y = y;
  this -> width = width;
  this -> height = height;
}
void RectangularObject::tick() { }
int RectangularObject::getX() { return x; }
int RectangularObject::getY() { return y; }
int RectangularObject::getWidth() { return width; }
int RectangularObject::getHeight() { return height; }
void RectangularObject::setX(int x) { this -> x = x; }
void RectangularObject::setY(int y) { this -> y = y; }
