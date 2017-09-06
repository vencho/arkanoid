#ifndef ABSTRACT_INPUT_HANDLER_H_DEFINED
#define ABSTRACT_INPUT_HANDLER_H_DEFINED
#include<SDL.h>
class AbstractInputHandler {
 public:
  virtual void handleInput(SDL_Event &e) = 0;
};
#endif
