#ifndef GAME_INPUT_HANDLER_H_DEFINED
#define GAME_INPUT_HANDLER_H_DEFINED
#include<AbstractInputHandler.h>
#include<SDL.h>
class Board;
class GameInputHandler : public AbstractInputHandler {
 private:
  Board &board;
 public:
  GameInputHandler(Board &board);
  virtual void handleInput(SDL_Event &e);
  virtual void handleInput();
};
#endif
