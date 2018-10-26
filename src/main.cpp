#include<Application.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  TTF_Init();
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

  Application arkanoid;

  while(!arkanoid.isFinished()) {
    arkanoid.tick();
  }
  TTF_Quit();
  SDL_Quit();

  return 0;
}
