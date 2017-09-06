#include<MenuInputHandler.h>
#include<SDL.h>
#include<Menu.h>
#include<MenuItem.h>
#include<MenuStack.h>

void MenuInputHandler::handleInput(SDL_Event &e) {
  if(e.type != SDL_KEYDOWN) return;

  switch(e.key.keysym.sym) {
  case SDLK_UP:
    menuStack.top() -> advanceSelection(-1);
    break;
  case SDLK_DOWN:
    menuStack.top() -> advanceSelection(1);
    break;
  case SDLK_LEFT:
    menuStack.top() -> getSelectedItem() -> left();
    break;
  case SDLK_RIGHT:
    menuStack.top() -> getSelectedItem() -> right();
    break;
  case SDLK_RETURN:
    menuStack.top() -> getSelectedItem() -> activate();
    break;
  };
}

MenuInputHandler::MenuInputHandler(MenuStack &menuStack) : menuStack(menuStack) { }




