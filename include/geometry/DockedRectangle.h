
#ifndef DOCKED_RECTANGLE_H_DEFINED
#define DOCKED_RECTANGLE_H_DEFINED

#include<geometry/FloatingRectangle.h>

class DockedRectangle : public FloatingRectangle {
 protected:
  int x, y;
 public:
  int & getX();
  int & getY();
  void setX(int x);
  void setY(int y);
  DockedRectangle(int x, int y, int width, int height);
};

#endif
