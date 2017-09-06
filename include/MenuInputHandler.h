#ifndef MENU_INPUT_HANDLER_H_DEFINED
#define MENU_INPUT_HANDLER_H_DEFINED
#include<AbstractInputHandler.h>
#include<SDL.h>
class Menu;
class MenuStack;

class MenuInputHandler : public AbstractInputHandler {
 private:
  MenuStack &menuStack;
 public:
  MenuInputHandler(MenuStack &menuStack);
  virtual void handleInput(SDL_Event &e);
};
#endif
