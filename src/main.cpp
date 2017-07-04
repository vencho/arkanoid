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


  Board B = Board(MAXX, MAXY);
  View V(B);
  bool quit = false;

  SDL_Event e;
  while(!quit) {

    t1 = clock();

    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_KEYDOWN) {
	if(e.key.keysym.sym == SDLK_q) {
	  quit = true;
	}
      }
    }

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
