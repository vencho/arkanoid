#ifndef MENU_PANE_H_DEFINED
#define MENU_PANE_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>
#include<DrawablePane.h>

class Menu;

class MenuPane : public DrawablePane {
 private:
  Menu & menu;
  int itemHeight;
  TTF_Font *font;
  SDL_Color selectedcolor, unselectedcolor;
  
 public:
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
  void handleInput(SDL_KeyboardEvent *e);
  MenuPane(Menu & menu, int width, int height);

};

#endif
