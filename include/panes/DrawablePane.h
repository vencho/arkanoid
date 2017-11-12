#ifndef DRAWABLE_PANE_H_DEFINED
#define DRAWABLE_PANE_H_DEFINED

#include<geometry/FloatingRectangle.h>
#include<SDL.h>

class DrawablePane : public FloatingRectangle {
 public:
  void draw(SDL_Surface *target, int baseX, int baseY);
  virtual void resetPane();
  DrawablePane();
 private:
  void setClip(SDL_Surface *target, int baseX, int baseY);
 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY) = 0;
};

#endif
