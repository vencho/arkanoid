#include<MenuNavigationCommand.h>
#include<Menu.h>
#include<Application.h>

void MenuNavigationCommand::execute() {
  application.menuNavigate(menu);
}

MenuNavigationCommand::MenuNavigationCommand(Menu *menu, Application &application) : application(application) {
  this -> menu = menu;
}

