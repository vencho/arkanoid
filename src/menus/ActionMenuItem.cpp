#include<menus/ActionMenuItem.h>
#include<menus/MenuItemDrawer.h>
#include<commands/AbstractCommand.h>

ActionMenuItem::ActionMenuItem(std::string text, 
			       bool selected, 
			       AbstractCommand &onActivate) 
  : MenuItem(text, selected), onActivate(onActivate) { }

void ActionMenuItem::drawYourself(MenuItemDrawer &mid) {
  mid.drawActionMenuItem(this);
}

void ActionMenuItem::activate() {
  onActivate.execute();
}

void ActionMenuItem::left() { }

void ActionMenuItem::right() { }


