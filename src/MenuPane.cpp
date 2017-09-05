#include<MenuPane.h>
#include<MenuItem.h>
#include<MenuItemDrawer.h>
#include<Menu.h>

void MenuPane::draw(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < menu.getNumItems(); i++) {
    MenuItem *item = menu.getItemByIndex(i);
    MenuItemDrawer mid(target, baseX, baseY + i*itemHeight, font, selectedcolor, unselectedcolor);
    item -> drawYourself(mid);
  }
}


MenuPane::MenuPane(Menu & menu, int width, int height) : menu(menu) {
  this -> width = width;
  this -> height = height;
  itemHeight = 50; // FIXME
  font = TTF_OpenFont("./res/fonts/Pacifico.ttf", 20);
  selectedcolor = {0, 255, 0};
  unselectedcolor = {255, 0, 0};
}



void MenuPane::handleInput(SDL_KeyboardEvent *e) {
  if(e -> type != SDL_KEYDOWN) return;

  SDL_Keycode sym = (e -> keysym).sym;
  if(sym == SDLK_UP) {
    menu.advanceSelection(-1);
  }
  else if(sym == SDLK_DOWN) {
    menu.advanceSelection(1);
  }
  else menu.getSelectedItem() -> handleInput(sym);
}

