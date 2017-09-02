#include<FloatingRectangle.h>

FloatingRectangle::FloatingRectangle(int width, int height) {
  this -> width = width;
  this -> height = height;
}
void FloatingRectangle::tick() { }
int & FloatingRectangle::getWidth() { return width; }
int & FloatingRectangle::getHeight() { return height; }
