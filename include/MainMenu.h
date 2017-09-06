#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include<Menu.h>
#include<string>
class MenuStack;
class Application;
class MainMenu : public Menu {
 private:
  Application &application;
 public:
  MainMenu(MenuStack &menuStack, Application &application);
};

#endif
