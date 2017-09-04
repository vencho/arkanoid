#include<BasicMenuItem.h>

BasicMenuItem::BasicMenuItem(std::string text, bool selected) : MenuItem(text, selected) { }
void BasicMenuItem::drawYourself(MenuItemDrawer &mid) {
  mid.drawBasicMenuItem(this);
}
