#ifndef MENU_ITEM_H_DEFINED
#define MENU_ITEM_H_DEFINED

#include<map>
#include<string>
#include<SDL.h>

class AbstractCommand;
class MenuItemDrawer;


class MenuItem {
 private:
  std::map<SDL_Keycode, AbstractCommand *> reaction;
  std::string text;
  bool selected;

 public:
  MenuItem(std::string text, bool selected);
  bool isSelected();
  void toggleSelect();
  void handleInput(SDL_Keycode sym);
  std::string getText();
  virtual void drawYourself(MenuItemDrawer &mid) = 0; 
};

#endif

