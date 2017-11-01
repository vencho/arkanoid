#include<menus/Menu.h>
#include<menus/MenuItem.h>

Menu::Menu(std::string title, Application &application) : application(application) {
  this -> title = title;
  whichSelected = 0;
}

int Menu::getNumItems() {
  return v.size();
}

MenuItem & Menu::getSelectedItem() {
  return *(v[whichSelected]);
}

MenuItem & Menu::getItemByIndex(int ind) {
  return *(v[ind]);
}

void Menu::advanceSelection(int howmuch) {
  if(v.size() == 0) return;
  getSelectedItem().toggleSelect(); 
  whichSelected = (whichSelected + howmuch) % getNumItems();
  if(whichSelected < 0) whichSelected += getNumItems();
  getSelectedItem().toggleSelect(); 
}

