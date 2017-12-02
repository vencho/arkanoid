#ifndef DRAWABLE_PANE_COMPOSITION_H_DEFINED
#define DRAWABLE_PANE_COMPOSITION_H_DEFINED

#include<geometry/FloatingRectangle.h>
#include<panes/DrawablePane.h>
#include<vector>
#include<memory>
#include<SDL.h>

class DrawablePaneComposition : public DrawablePane {
 protected:
  bool vertical;
  std::vector<std::unique_ptr<DrawablePane>> panes;
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
  
 public:
  DrawablePaneComposition(bool vertical);
  virtual void reset();
  void addPane(std::unique_ptr<DrawablePane> pane);

};

#endif
