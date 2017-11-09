#include<Application.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  Application arkanoid;

  while(!arkanoid.isFinished()) {
    arkanoid.tick();
  }
  TTF_Quit();
  SDL_Quit();

  return 0;
}
