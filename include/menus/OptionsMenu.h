#ifndef OPTIONS_MENU_H_DEFINED
#define OPTIONS_MENU_H_DEFINED
#include<menus/Menu.h>
class Application;
class OptionsMenu : public Menu {
 public:
  OptionsMenu(Application &application);
};
#endif
