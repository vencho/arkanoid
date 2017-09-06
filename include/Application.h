#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED
#include<SDL.h>
#include<MenuStack.h>

class DrawablePane;
class GamePane;
class Menu;
class MenuPane;
class AbstractInputHandler;

class Application {
 private:
  SDL_Surface *screen;
  SDL_Window *window;
  bool haveFinished;
  bool menuMode;

  DrawablePane *gamePane, *menuPane;
  AbstractInputHandler *gameInputHandler, *menuInputHandler; 
  Menu *mainMenu;
  MenuStack menuStack;
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
