#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include<SDL.h>
#include<vector>
#include<string>

class MenuItem;
class MenuStack;

class Menu {
 private:
  std::string title;
  std::vector<MenuItem *> v;
  int whichSelected;
  MenuStack &menuStack;
  
 public:
  Menu(std::string title, MenuStack &menuStack);
  ~Menu();
  void addMenuItem(MenuItem *item);
  int getNumItems();
  MenuItem * getItemByIndex(int ind);
  void advanceSelection(int howmuch);
  MenuItem * getSelectedItem();
  MenuStack & getMenuStack();

};

#endif
