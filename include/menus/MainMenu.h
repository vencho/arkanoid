#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include<menus/Menu.h>
#include<string>
class Application;
class MainMenu : public Menu {
 public:
  MainMenu(Application &application);
};

#endif
