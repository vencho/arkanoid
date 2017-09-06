#ifndef MENU_ITEM_DRAWER_H_DEFINED
#define MENU_ITEM_DRAWER_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>

class ActionMenuItem;
class NavigationMenuItem;
class MenuItem;

class MenuItemDrawer {
 private:
  SDL_Surface *target;
  int baseX, baseY;
  TTF_Font *font;
  SDL_Color selectedcolor, unselectedcolor;

  void simpleitemdraw(MenuItem *elt);

  
 public:
  MenuItemDrawer(SDL_Surface *target, int baseX, int baseY, TTF_Font *font, SDL_Color selectedcolor, SDL_Color unselectedcolor);


  void drawActionMenuItem(ActionMenuItem *elt);
  void drawNavigationMenuItem(NavigationMenuItem *elt);
};
#endif
