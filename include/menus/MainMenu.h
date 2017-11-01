#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include<menus/Menu.h>
#include<menus/OptionsMenu.h>
#include<string>
class Application;
class MainMenu : public Menu {
 public:
  MainMenu(Application &application);
 private:
  std::unique_ptr<OptionsMenu> options;
};

#endif
