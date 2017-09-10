#include<panes/MenuPane.h>
#include<menus/MenuItem.h>
#include<menus/MenuItemDrawer.h>
#include<menus/Menu.h>
#include<SDL.h>
#include<stack>

void MenuPane::draw(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  r.x = baseX;
  r.y = baseY;
  r.w = width;
  r.h = height;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0, 0, 0));
  
  Menu *menu = menuStack.top();
  for(int i = 0; i < menu -> getNumItems(); i++) {
    MenuItem *item = menu -> getItemByIndex(i);
    MenuItemDrawer mid(target, baseX, baseY + i*itemHeight, font, selectedcolor, unselectedcolor);
    item -> drawYourself(mid);
  }
}


MenuPane::MenuPane(std::stack<Menu *> &menuStack, int width, int height) : menuStack(menuStack) {
  this -> width = width;
  this -> height = height;
  itemHeight = 50;
  font = TTF_OpenFont("./res/fonts/Pacifico.ttf", 20);
  selectedcolor = {0, 255, 0};
  unselectedcolor = {255, 0, 0};
}

