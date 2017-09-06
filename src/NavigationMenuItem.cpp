#include<string>
#include<MenuItem.h>
#include<NavigationMenuItem.h>
#include<MenuItemDrawer.h>
#include<Menu.h>
#include<MenuStack.h>


NavigationMenuItem::NavigationMenuItem(std::string text, bool selected, Menu *next, Menu &owner) :
  MenuItem(text, selected), owner(owner) {
  this -> next = next;
}

void NavigationMenuItem::drawYourself(MenuItemDrawer &mid) {
  mid.drawNavigationMenuItem(this);
}

void NavigationMenuItem::activate() {
  if(next) {
    owner.getMenuStack().push(next);
  }
  else {
    owner.getMenuStack().pop();
  }
}

void NavigationMenuItem::left() { }

void NavigationMenuItem::right() { }


