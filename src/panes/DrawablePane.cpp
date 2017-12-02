#include<panes/DrawablePane.h>

DrawablePane::DrawablePane() : FloatingRectangle(0, 0) { }
void DrawablePane::reset() { }

void DrawablePane::draw(SDL_Surface *target, int baseX, int baseY) {
  setClip(target, baseX, baseY);
  drawYourself(target, baseX, baseY);
}

void DrawablePane::setClip(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect clip;
  clip.x = baseX;
  clip.y = baseY;
  clip.w = width;
  clip.h = height;
  SDL_SetClipRect(target, &clip);
}

