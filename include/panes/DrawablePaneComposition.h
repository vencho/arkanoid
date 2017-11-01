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

 public:
  DrawablePaneComposition(bool vertical);
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
  virtual void resetPane();
  void addPane(std::unique_ptr<DrawablePane> pane);

};

#endif
