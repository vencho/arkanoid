#ifndef MENU_ITEM_H_DEFINED
#define MENU_ITEM_H_DEFINED

#include<map>
#include<string>
#include<SDL.h>

class MenuItemDrawer;


class MenuItem {
 private:
  std::string text;
  bool selected;

 public:
  MenuItem(std::string text, bool selected);
  bool isSelected();
  void toggleSelect();
  std::string getText();
  
  virtual void activate() = 0;
  virtual void left() = 0;
  virtual void right() = 0;
  virtual void drawYourself(MenuItemDrawer &mid) = 0; 
};

#endif

