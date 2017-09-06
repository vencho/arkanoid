#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include<Menu.h>
#include<string>
class MenuStack;

class MainMenu : public Menu {
public:
  MainMenu(MenuStack &menuStack);
};

#endif
