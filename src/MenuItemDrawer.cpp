
#include<MenuItemDrawer.h>
#include<MenuItem.h>
#include<SDL.h>
#include<SDL_ttf.h>


MenuItemDrawer::MenuItemDrawer(SDL_Surface *target, int baseX, int baseY, 
			       TTF_Font *font, SDL_Color selectedcolor, SDL_Color unselectedcolor) {
  this -> target = target;
  this -> baseX = baseX;
  this -> baseY = baseY;
  this -> font = font;
  this -> selectedcolor = selectedcolor;
  this -> unselectedcolor = unselectedcolor;
}

void MenuItemDrawer::drawActionMenuItem(ActionMenuItem *elt) {
  simpleitemdraw((MenuItem *)elt);
}

void MenuItemDrawer::drawNavigationMenuItem(NavigationMenuItem *elt) {
  simpleitemdraw((MenuItem *) elt);
}

void MenuItemDrawer::simpleitemdraw(MenuItem *elt) {
  std::string text = elt -> getText();
  SDL_Surface *textsurface = elt -> isSelected() ? 
    TTF_RenderText_Solid(font, text.c_str(), selectedcolor) :
    TTF_RenderText_Solid(font, text.c_str(), unselectedcolor);

  SDL_Rect r;
  r.x = baseX; 
  r.y = baseY;

  r.x = baseX;
  r.y = baseY;
  SDL_BlitSurface(textsurface, NULL, target, &r);
  SDL_FreeSurface(textsurface);
}


