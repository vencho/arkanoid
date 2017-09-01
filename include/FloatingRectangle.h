#ifndef FLOATINGRECTANGLE_H_INCLUDED
#define FLOATINGRECTANGLE_H_INCLUDED

class FloatingRectangle {
 protected:
  int width, height;
 public:
  FloatingRectangle(int width, int height);
  virtual void tick();
  int getWidth();
  int getHeight();
};

#endif
