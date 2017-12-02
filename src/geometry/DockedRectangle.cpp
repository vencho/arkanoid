#include<geometry/DockedRectangle.h>

void DockedRectangle::setX(int x) {
  scaledX = x*denominator;
}

void DockedRectangle::setY(int y) { 
  scaledY = y*denominator;
}

int DockedRectangle::getX() const { 
  int whole = scaledX / denominator;
  int remainder = scaledX % denominator;
  if(remainder >= denominator / 2) whole++;
  else if(remainder < -denominator / 2) whole--;
  return whole;
}

int DockedRectangle::getY() const { 
  int whole = scaledY / denominator;
  int remainder = scaledY % denominator;
  if(remainder >= denominator / 2) whole++;
  else if(remainder < -denominator / 2) whole--;
  return whole;
}

DockedRectangle::DockedRectangle(int x, int y, int width, int height) 
  : FloatingRectangle(width, height) { 
  setX(x);
  setY(y);
}

DockedRectangle::DockedRectangle() {

}
