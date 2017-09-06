#ifndef NAVIGATION_MENU_ITEM_H_INCLUDED
#define NAVIGATION_MENU_ITEM_H_INCLUDED

#include<string>
#include<MenuItem.h>

class MenuItemDrawer;
class Menu;

class NavigationMenuItem : public MenuItem {
 private:
  Menu *next;
  Menu &owner;
 public:
  NavigationMenuItem(std::string text, bool selected, Menu *next, Menu &owner);
  virtual void drawYourself(MenuItemDrawer &mid);
  virtual void activate();
  virtual void left();
  virtual void right();
};

#endif
