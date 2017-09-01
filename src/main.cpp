#include<Board.h>
#include<Global.h>
#include<SDL.h>
#include<View.h>
#include<ctime>


int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Arkanoid", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH,
					SCREEN_HEIGHT,
					0);
  SDL_Surface *screen = SDL_GetWindowSurface(window);
  SDL_Surface *game;
  
  clock_t t1, t2;
  double secondsspent;
  clock();


  Board B(MAXX, MAXY);
  View V(B);
  bool quit = false;

  SDL_Event e;
  while(!quit) {

    t1 = clock();

    while(SDL_PollEvent(&e)) {
      /*
      if(e.type == SDL_KEYDOWN) {
	if(e.key.keysym.sym == SDLK_q) {
	  quit = true;
	}
      }
      */
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    Uint8 leftPressed = currentKeyStates[SDL_SCANCODE_A];
    Uint8 rightPressed = currentKeyStates[SDL_SCANCODE_D];
    int dx;
    if( (leftPressed ^ rightPressed) == 0 ) { dx = 0; } 
    else if(leftPressed) { dx = -1; } 
    else { dx = 1; }
    B.getPaddle().setVelocity(dx*PADDLE_SPEED, 0);

    if(currentKeyStates[SDL_SCANCODE_Q]) quit = true;

    if(currentKeyStates[SDL_SCANCODE_W]) B.initialiseBalls();

    B.tick();

    game = V.draw();
    SDL_BlitSurface(game, NULL, screen, NULL);
    SDL_FreeSurface(game);
    SDL_UpdateWindowSurface(window);
    
    t2 = clock();
    double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;
    int delay = (int)(1000*(SPF - secondsspent));
    SDL_Delay(delay);
  }

  SDL_Quit();
  return 0;
}
