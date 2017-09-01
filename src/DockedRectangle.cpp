#include<DockedRectangle.h>

void DockedRectangle::setX(int x) { this -> x = x; }
void DockedRectangle::setY(int y) { this -> y = y; }
int DockedRectangle::getX() { return x; }
int DockedRectangle::getY() { return y; }
DockedRectangle::DockedRectangle(int x, int y, int width, int height) : FloatingRectangle(width, height), x(x), y(y) { }
