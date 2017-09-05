#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED
#include<SDL.h>

class DrawablePane;


class Application {
 private:
  SDL_Surface *screen;
  SDL_Window *window;
  DrawablePane *currentDisplay;
  DrawablePane *mainMenu, *optionsMenu, *gameScreen;
  bool ended;

  void handleInput();

 public:
  Application();
  void start();
  void end();
  void tick();
  bool isFinished();
  void setActivePane(DrawablePane *pane);
};


#endif
