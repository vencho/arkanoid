#include<Menu.h>
#include<MenuItem.h>

Menu::Menu(std::string title) { 
  this -> title = title;
  whichSelected = 0;
}

Menu::~Menu() {
  for(int i = 0; i < getNumItems(); i++) {
    delete v[i];
  }
}

int Menu::getNumItems() {
  return v.size();
}

MenuItem * Menu::getSelectedItem() {
  return v[whichSelected];
}

MenuItem * Menu::getItemByIndex(int ind) {
  return v[ind];
}

void Menu::addMenuItem(MenuItem *item) {
  v.push_back(item);
}

void Menu::advanceSelection(int howmuch) {
  if(v.size() == 0) return;

  v[whichSelected] -> toggleSelect(); 
  whichSelected += howmuch;
  whichSelected %= v.size();
  if(whichSelected < 0) whichSelected += v.size();
  v[whichSelected] -> toggleSelect(); 
}

