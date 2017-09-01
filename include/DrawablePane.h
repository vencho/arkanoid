#ifndef DRAWABLE_PANE_H_DEFINED
#define DRAWABLE_PANE_H_DEFINED

#include<SDL.h>
#include<FloatingRectangle.h>


class DrawablePane : public FloatingRectangle {
 public:
  virtual void draw(SDL_Surface *target, int baseX, int baseY) = 0;
  DrawablePane();
};

#endif
