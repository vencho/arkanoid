#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include<SDL.h>
#include<vector>
#include<string>

class MenuItem;
class Application;

class Menu {
 protected:
  Application &application;
  std::string title;
  std::vector<MenuItem *> v;
  int whichSelected;

 public:
  Menu(std::string title, Application &application);
  ~Menu();
  void addMenuItem(MenuItem *item);
  int getNumItems();
  MenuItem * getItemByIndex(int ind);
  void advanceSelection(int howmuch);
  MenuItem * getSelectedItem();
};

#endif
