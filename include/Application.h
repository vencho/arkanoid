#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED
#include<SDL.h>
#include<stack>

class DrawablePane;
class GamePane;
class Menu;
class MenuPane;
class AbstractInputHandler;
class Board;

class Application {
 private:
  SDL_Surface *screen;
  SDL_Window *window;
  bool haveFinished;
  bool menuMode;

  DrawablePane *gamePane, *menuPane;
  AbstractInputHandler *gameInputHandler, *menuInputHandler; 
  Menu *mainMenu;
  std::stack<Menu *> menuStack;
  Board *board;

  void handleInput();
  void end();

 public:
  Application();
  void start();
  void requestEnd();
  void tick();
  bool isFinished();
  void setActivePane(DrawablePane *pane);
  void switchToGameMode();
  void switchToMenuMode();
  void menuNavigate(Menu *menu);
};


#endif
