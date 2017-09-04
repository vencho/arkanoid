#ifndef MENU_ITEM_DRAWER_H_DEFINED
#define MENU_ITEM_DRAWER_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>

class BasicMenuItem;

class MenuItemDrawer {
 private:
  SDL_Surface *target;
  int baseX, baseY;
  TTF_Font *font;
  SDL_Color textcolor;
 public:
  MenuItemDrawer(SDL_Surface *target, int baseX, int baseY, TTF_Font *font, SDL_Color textcolor);
  void drawBasicMenuItem(BasicMenuItem *elt);
};
#endif
