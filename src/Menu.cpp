#include<Menu.h>

Menu::Menu(std::string title) { 
  this -> title = title;
}

int Menu::getNumItems() {
  return v.size();
}

MenuItem * Menu::getItemByIndex(int ind) {
  return v[ind];
}

void Menu::addMenuItem(MenuItem *item) {
  v.push_back(item);
}

void Menu::handleInput(SDL_KeyboardEvent *e) {
  if(e -> type != SDL_KEYDOWN) return;
  
  if(v.empty()) return;
    
  SDL_Keycode sym = (e -> keysym).sym;
  if(sym == SDLK_UP) { 
    v[whichSelected] -> toggleSelect(); 
    whichSelected = (whichSelected - 1 + v.size()) % v.size();
    v[whichSelected] -> toggleSelect();
  }
  else if(sym == SDLK_DOWN) {
    v[whichSelected] -> toggleSelect(); 
    whichSelected = (whichSelected + 1) % v.size();
    v[whichSelected] -> toggleSelect(); 
  }
  else v[whichSelected] -> handleInput(sym);
}
