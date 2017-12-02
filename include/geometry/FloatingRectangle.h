#ifndef FLOATINGRECTANGLE_H_INCLUDED
#define FLOATINGRECTANGLE_H_INCLUDED

class FloatingRectangle {
 protected:
  int width, height;
 public:
  FloatingRectangle();
  FloatingRectangle(int width, int height);
  virtual void tick();
  int getWidth() const;
  int getHeight() const;
};

#endif
