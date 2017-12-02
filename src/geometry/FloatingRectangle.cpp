#include<geometry/FloatingRectangle.h>

FloatingRectangle::FloatingRectangle() {

}

FloatingRectangle::FloatingRectangle(int width, int height) {
  this -> width = width;
  this -> height = height;
}
void FloatingRectangle::tick() { }
int FloatingRectangle::getWidth() const { return width; }
int FloatingRectangle::getHeight() const { return height; }
