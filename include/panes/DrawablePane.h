#ifndef DRAWABLE_PANE_H_DEFINED
#define DRAWABLE_PANE_H_DEFINED

#include<geometry/FloatingRectangle.h>
#include<SDL.h>

class DrawablePane : public FloatingRectangle {
 public:
  virtual void draw(SDL_Surface *target, int baseX, int baseY) = 0;
  virtual void tick();
  virtual void resetPane();
  DrawablePane();
};

#endif
