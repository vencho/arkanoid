
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
  /* Upper right corner, rounded to nearest pixel. */
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);

  int getScaledX() const;
  int getScaledY() const;
  static int getPositionDenominator();

  DockedRectangle(int x, int y, int width, int height);
  DockedRectangle();
};

#endif
