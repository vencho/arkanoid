#ifndef MENU_NAVIGATION_COMMAND_H_INCLUDED
#define MENU_NAVIGATION_COMMAND_H_INCLUDED
#include<commands/AbstractCommand.h>
class Menu;
class Application;
class MenuNavigationCommand : public AbstractCommand {
 private:
  Application &application;
  Menu *menu;
 public:
  virtual void execute();
  MenuNavigationCommand(Menu *, Application &application);
};

#endif
