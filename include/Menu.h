#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include<SDL.h>
#include<vector>
#include<string>

class MenuItem;

class Menu {
 private:
  std::string title;
  std::vector<MenuItem *> v;
  int whichSelected;

 public:
  Menu(std::string title);
  ~Menu();
  void addMenuItem(MenuItem *item);
  int getNumItems();
  MenuItem * getItemByIndex(int ind);
  void advanceSelection(int howmuch);
  MenuItem * getSelectedItem();
};

#endif
