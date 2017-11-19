
#ifndef DOCKED_RECTANGLE_H_DEFINED
#define DOCKED_RECTANGLE_H_DEFINED

#include<geometry/FloatingRectangle.h>

class DockedRectangle : public FloatingRectangle {
 protected:
  /* 
     We divide each pixel into denominator pieces in both dimensions.
     The position of the upper right corner of the rectangle is
     (scaledX, scaledY) / denominator.
  */
  int scaledX, scaledY;
  const static int denominator = 1000;

 public:
  /* 
     Upper right corner, rounded to nearest pixel.
  */
  int getX();
  int getY();
  void setX(int x);
  void setY(int y);
  DockedRectangle(int x, int y, int width, int height);
};

#endif
