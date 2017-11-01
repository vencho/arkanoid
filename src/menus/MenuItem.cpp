#include<menus/MenuItem.h>
#include<commands/AbstractCommand.h>

MenuItem::MenuItem(std::string text, bool selected) {
  this -> text = text;
  this -> selected = selected;
}

bool MenuItem::isSelected() {
  return selected;
}

void MenuItem::toggleSelect() {
  selected ^= 1;
}

std::string MenuItem::getText() {
  return text;
}


