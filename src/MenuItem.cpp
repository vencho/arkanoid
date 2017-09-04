#include<MenuItem.h>
#include<AbstractCommand.h>


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

void MenuItem::handleInput(SDL_Keycode sym) {
  if(reaction.find( sym ) == reaction.end()) return;
  reaction[ sym ] -> execute();
}

std::string MenuItem::getText() {
  return text;
}
