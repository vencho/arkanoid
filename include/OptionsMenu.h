#ifndef OPTIONS_MENU_H_DEFINED
#define OPTIONS_MENU_H_DEFINED
#include<Menu.h>
class MenuStack;
class OptionsMenu : public Menu {
 public:
  OptionsMenu(MenuStack &menuStack);
};
#endif
