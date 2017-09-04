#include<MenuPane.h>
#include<MenuItem.h>
#include<MenuItemDrawer.h>
#include<Menu.h>

void MenuPane::draw(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < menu.getNumItems(); i++) {
    MenuItem *item = menu.getItemByIndex(i);
    MenuItemDrawer mid(target, baseX, baseY + i*itemHeight, font, textcolor);
    item -> drawYourself(mid);
  }
}


MenuPane::MenuPane(Menu & menu, int width, int height) : menu(menu) {
    this -> width = width;
    this -> height = height;
    itemHeight = 50; // FIXME
    font = TTF_OpenFont("./res/fonts/Pacifico.ttf", 20);
    textcolor = {0, 255, 0};
}
