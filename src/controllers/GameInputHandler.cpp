#include<SDL.h>
#include<controllers/GameInputHandler.h>
#include<model/Board.h>
#include<model/Paddle.h>
GameInputHandler::GameInputHandler(Board &board) : board(board) { }
void GameInputHandler::handleInput(SDL_Event &e) { 
  if(e.type == SDL_KEYDOWN) {
    // cheat code for debugging
    if(e.key.keysym.sym == SDLK_i) {
      board.consumePowerup('D');
    }
  }
}

void GameInputHandler::handleInput() {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  Uint8 leftPressed = currentKeyStates[SDL_SCANCODE_A];
  Uint8 rightPressed = currentKeyStates[SDL_SCANCODE_D];
  int dx;
  if( (leftPressed ^ rightPressed) == 0 ) { dx = 0; } 
  else if(leftPressed) { dx = -1; } 
  else { dx = 1; }

  board.getPaddle().setVelocity(dx*PADDLE_SPEED, 0);

  if(currentKeyStates[SDL_SCANCODE_W]) board.unstickBalls();
  if(currentKeyStates[SDL_SCANCODE_SPACE]) board.fireBullets();
  
  // cheat codes for debugging
  if(currentKeyStates[SDL_SCANCODE_O]) board.consumePowerup('E');
  if(currentKeyStates[SDL_SCANCODE_P]) board.consumePowerup('C');
  if(currentKeyStates[SDL_SCANCODE_L]) board.consumePowerup('L');
  if(currentKeyStates[SDL_SCANCODE_K]) board.consumePowerup('S');
}

