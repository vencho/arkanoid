#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED
#include<SDL.h>
#include<SDL_image.h>
#include<stack>
#include<memory>
#include<model/Board.h>
#include<menus/MainMenu.h>
#include<panes/GamePane.h>
#include<panes/MenuPane.h>
#include<controllers/AbstractInputHandler.h>

class DrawablePane;
class Menu;

class Application {
 private:
  SDL_Surface *screen;
  SDL_Window *window;
  bool haveFinished;
  bool menuMode;


  Board board;
  std::unique_ptr<GamePane> gamePane;
  std::unique_ptr<MenuPane> menuPane;
  std::unique_ptr<AbstractInputHandler> gameInputHandler, menuInputHandler;
  std::unique_ptr<MainMenu> mainMenu;

  std::stack<Menu *> menuStack;

  void handleInput();
  void end();

 public:
  Application();
  void start();
  void requestEnd();
  void tick();
  bool isFinished();
  void switchToGameMode();
  void switchToMenuMode();
  void menuNavigate(Menu *menu);
};


#endif
