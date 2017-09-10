#ifndef ACTION_MENU_ITEM_H_INCLUDED
#define ACTION_MENU_ITEM_H_INCLUDED

#include<string>
#include<menus/MenuItem.h>

class MenuItemDrawer;
class AbstractCommand;

class ActionMenuItem : public MenuItem {
 private:
  AbstractCommand &onActivate;

 public:
  ActionMenuItem(std::string text, bool selected, AbstractCommand &onActivate);
  virtual void drawYourself(MenuItemDrawer &mid);
  virtual void activate();
  virtual void left();
  virtual void right();
};

#endif
