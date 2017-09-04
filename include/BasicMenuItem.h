#ifndef BASIC_MENU_ITEM_H_INCLUDED
#define BASIC_MENU_ITEM_H_INCLUDED

#include<string>
#include<MenuItem.h>

class MenuItemDrawer;


class BasicMenuItem : public MenuItem {
 public:
  BasicMenuItem(std::string text, bool selected);
  virtual void drawYourself(MenuItemDrawer &mid);
};

#endif
