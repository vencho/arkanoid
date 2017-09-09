#ifndef SET_VALUE_MENU_ITEM_H_INCLUDED
#define SET_VALUE_MENU_ITEM_H_INCLUDED
#include<string>
#include<MenuItem.h>

class MenuItemDrawer;

class SetValueMenuItem : public MenuItem {
 private:
  const int &min, &max;
  int &val;

 public:
 SetValueMenuItem(std::string text, 
		  bool selected, 
		  const int &min, 
		  const int &max, 
		  int &val);
  int getVal();
  virtual void drawYourself(MenuItemDrawer &mid);
  virtual void activate();
  virtual void left();
  virtual void right();
};

#endif
