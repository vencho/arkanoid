#include<SDL.h>
#include<controllers/GameInputHandler.h>
#include<model/Board.h>
#include<model/Paddle.h>
GameInputHandler::GameInputHandler(Board &board) : board(board) { }
void GameInputHandler::handleInput(SDL_Event &e) { }
void GameInputHandler::handleInput() {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  Uint8 leftPressed = currentKeyStates[SDL_SCANCODE_A];
  Uint8 rightPressed = currentKeyStates[SDL_SCANCODE_D];
  int dx;
  if( (leftPressed ^ rightPressed) == 0 ) { dx = 0; } 
  else if(leftPressed) { dx = -1; } 
  else { dx = 1; }

  board.getPaddle().setVelocity(dx*PADDLE_SPEED, 0);

  if(currentKeyStates[SDL_SCANCODE_W]) board.initialiseBalls();
}

