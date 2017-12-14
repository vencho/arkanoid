#include<commands/MenuNavigationCommand.h>
#include<menus/Menu.h>
#include<Application.h>

void MenuNavigationCommand::execute() {
  if(menu != nullptr) {
    menu -> advanceSelection(menu -> getNumItems() - menu -> getSelectedIndex());
  }
  application.menuNavigate(menu);
}

MenuNavigationCommand::MenuNavigationCommand(Menu *menu, Application &application) : application(application) {
  this -> menu = menu;
}

