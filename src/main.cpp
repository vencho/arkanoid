#include<Application.h>
#include<Sound.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  TTF_Init();
  Sound::initSound();

  Application arkanoid;

  while(!arkanoid.isFinished()) {
    arkanoid.tick();
  }
  TTF_Quit();
  SDL_Quit();

  return 0;
}
