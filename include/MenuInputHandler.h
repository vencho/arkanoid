#ifndef MENU_INPUT_HANDLER_H_DEFINED
#define MENU_INPUT_HANDLER_H_DEFINED
#include<AbstractInputHandler.h>
#include<stack>
#include<SDL.h>
class Menu;

class MenuInputHandler : public AbstractInputHandler {
 private:
  std::stack<Menu *> &menuStack;
 public:
  MenuInputHandler(std::stack<Menu *> &menuStack);
  virtual void handleInput(SDL_Event &e);
  virtual void handleInput();
};
#endif
