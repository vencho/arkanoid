#include<Application.h>
#include<MenuPane.h>
#include<Menu.h>
#include<Global.h>
#include<Board.h>
#include<DrawablePaneComposition.h>
#include<GameScreen.h>
#include<ScorePane.h>
#include<MainMenu.h>
#include<OptionsMenu.h>
#include<MenuPane.h>
#include<GamePane.h>
#include<MenuInputHandler.h>
#include<GameInputHandler.h>
#include<Configuration.h>
#include<string>

Application::Application() {
  haveFinished = true;
}

bool Application::isFinished() {
  return haveFinished;
}

void Application::start() {
  haveFinished = false;
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  window = SDL_CreateWindow("Arkanoid", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH,
					SCREEN_HEIGHT,
					0);
  screen = SDL_GetWindowSurface(window);
  menuMode = true;

  mainMenu = new MainMenu(*this);
  menuStack.push(mainMenu);
  menuPane = new MenuPane(menuStack, SCREEN_WIDTH, SCREEN_HEIGHT);
  menuInputHandler = new MenuInputHandler(menuStack);

  board = NULL;
}

void Application::handleInput() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) { 
    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q) { 
      requestEnd();
      return; 
    }

    if(menuMode) menuInputHandler -> handleInput(e);
    else gameInputHandler -> handleInput(e);
  }

  if(menuMode) menuInputHandler -> handleInput();
  else gameInputHandler -> handleInput();
}

void Application::tick() {
  if(isFinished()) return;

  double t1, t2;
  t1 = clock();

  handleInput();
  if(isFinished()) return;

  if(menuMode) menuPane -> tick();
  else gamePane -> tick();

  if(menuMode) menuPane -> draw(screen, (SCREEN_WIDTH-GAME_SCREEN_WIDTH)/2, 0); 
  else gamePane -> draw(screen, (SCREEN_WIDTH-GAME_SCREEN_WIDTH)/2, 0);
  
  SDL_UpdateWindowSurface(window);

  t2 = clock();
  double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;
  int delay = (int)(1000*(SPF - secondsspent));
  SDL_Delay(delay);

  if(!menuMode && board -> numTiles() == 0) switchToMenuMode();
}

void Application::requestEnd() {
  haveFinished = true;
}

void Application::end() {
  if(menuMode) {
    delete menuPane;
    delete menuInputHandler;
    delete mainMenu;
  }
  else {
    delete gamePane;
    delete board;
  }
  /*
    FIXME Clean up operations. Destroy everything.
  */

  haveFinished = true;
  /*
  if(mainMenuPane) delete mainMenuPane;
  if(gameScreenPane) delete gameScreenPane;
  */
  
  SDL_FreeSurface(screen);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

void Application::menuNavigate(Menu *menu) {
  if(menu == NULL)
    menuStack.pop();
  else
    menuStack.push(menu);
}

void Application::switchToMenuMode() {
  delete board;
  board = NULL;  
  delete gamePane;
  delete gameInputHandler;

  menuMode = true;
}

void Application::switchToGameMode() {
  menuMode = false;
  if(board != NULL) {
    return;
  }
 
  char lvl[4];
  sprintf(lvl, "%d", Configuration::level);
  std::string level(lvl);
  std::string levelpath = "levels/level" + level + ".txt";
  board = new Board(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, levelpath);
  gamePane = new GamePane(board);
  gameInputHandler = new GameInputHandler(*board);
}

