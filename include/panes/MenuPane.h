#ifndef MENU_PANE_H_DEFINED
#define MENU_PANE_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>
#include<stack>
#include<panes/DrawablePane.h>

class Menu;

class MenuPane : public DrawablePane {
 private:
  std::stack<Menu *> & menuStack;
  int itemHeight;
  TTF_Font *font;
  SDL_Color selectedcolor, unselectedcolor;
  
 public:
  MenuPane(std::stack<Menu *> &menuStack, int width, int height);
 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
};

#endif
