#ifndef RECTOBJ_H_INCLUDED
#define RECTOBJ_H_INCLUDED

class RectangularObject {
 protected:
  int x, y, width, height;
 public:
  RectangularObject(int x, int y, int width, int height);
  virtual void tick();
  int getX();
  int getY();
  int getWidth();
  int getHeight();
};

#endif
