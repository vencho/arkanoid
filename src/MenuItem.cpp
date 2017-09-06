#include<MenuItem.h>
#include<AbstractCommand.h>


MenuItem::MenuItem(std::string text, bool selected) {
  this -> text = text;
  this -> selected = selected;
}

MenuItem::~MenuItem() {

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

