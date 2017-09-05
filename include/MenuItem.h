#ifndef MENU_ITEM_H_DEFINED
#define MENU_ITEM_H_DEFINED

#include<map>
#include<string>
#include<SDL.h>

class AbstractCommand;
class MenuItemDrawer;


class MenuItem {
 private:
  // FIXME who is responsible for cleaning up the commands?
  std::map<SDL_Keycode, AbstractCommand *> reaction;
  std::string text;
  bool selected;

 public:
  void addReaction(SDL_Keycode key, AbstractCommand *command);
  MenuItem(std::string text, bool selected);
  ~MenuItem();
  bool isSelected();
  void toggleSelect();
  void handleInput(SDL_Keycode sym);
  std::string getText();
  virtual void drawYourself(MenuItemDrawer &mid) = 0; 
};

#endif

