#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include<SDL.h>
#include<vector>
#include<string>
#include<memory>
#include<menus/MenuItem.h>
class Application;

class Menu {
 protected:
  Application &application;
  std::string title;
  std::vector<std::unique_ptr<MenuItem>> v;
  int whichSelected;

 public:
  Menu(std::string title, Application &application);
  int getNumItems();
  void advanceSelection(int howmuch);
  MenuItem & getItemByIndex(int ind);
  MenuItem & getSelectedItem();
};

#endif
