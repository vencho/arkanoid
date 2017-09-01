#ifndef DRAWABLE_PANE_COMPOSITION_H_DEFINED
#define DRAWABLE_PANE_COMPOSITION_H_DEFINED

#include<DrawablePane.h>
#include<vector>
#include<SDL.h>
#include<FloatingRectangle.h>

class DrawablePaneComposition : public DrawablePane {
  bool vertical;
  std::vector<DrawablePane *> panes;

 public:
  DrawablePaneComposition(bool vertical);
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
  void addPane(DrawablePane *pane);
};

#endif
