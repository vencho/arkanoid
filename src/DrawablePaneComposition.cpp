#include<DrawablePaneComposition.h>

DrawablePaneComposition::DrawablePaneComposition(bool vertical) { 
  this -> vertical = vertical;
  this -> width = 0;
  this -> height = 0;
}


void DrawablePaneComposition::draw(SDL_Surface *target, int baseX, int baseY) {
  int offsetX, offsetY;
  offsetX = offsetY = 0;
  for(int i = 0; i < panes.size(); i++) {
    panes[i] -> draw(target, baseX + offsetX, baseY + offsetY);
    int & offset = vertical ? offsetY : offsetX;
    int amount = vertical ? panes[i] -> getHeight() : panes[i] -> getWidth();
    offset += amount;
  }
}


void DrawablePaneComposition::addPane(DrawablePane *pane) {
  panes.push_back(pane);
  if(vertical) {
    if(pane -> getWidth() > width) width = pane -> getWidth();
    height += pane -> getHeight();
  }
  else {
    if(pane -> getHeight() > height) height = pane -> getHeight();
    width += pane -> getWidth();
  }
}
