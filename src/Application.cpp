#include<string>
#include<Application.h>
#include<Configuration.h>

#include<model/Board.h>

#include<panes/GameScreen.h>
#include<panes/ScorePane.h>
#include<panes/MenuPane.h>
#include<panes/GamePane.h>
#include<panes/MenuPane.h>
#include<panes/DrawablePaneComposition.h>

#include<menus/MainMenu.h>
#include<menus/OptionsMenu.h>
#include<menus/Menu.h>

#include<controllers/MenuInputHandler.h>
#include<controllers/GameInputHandler.h>


Application::Application() : mainMenu(new MainMenu(*this)), 
			     menuInputHandler(new MenuInputHandler(menuStack)),
			     gameInputHandler(new GameInputHandler(board)),
			     gamePane(new GamePane(board)),
			     menuPane(new MenuPane(menuStack, screenWidth, screenHeight)) {
  haveFinished = false;
  menuMode = true;
  menuStack.push(mainMenu.get());

  window = SDL_CreateWindow("Arkanoid", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					screenWidth,
					screenHeight,
					0);
  screen = SDL_GetWindowSurface(window);
}

bool Application::isFinished() {
  return haveFinished;
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

  if(menuMode) menuPane -> draw(screen, (screenWidth-GameScreen::gameScreenWidth)/2, 0); 
  else {
    board.tick();
    gamePane -> draw(screen, (screenWidth-GameScreen::gameScreenWidth)/2, 0);
  }
  SDL_UpdateWindowSurface(window);

  t2 = clock();
  int msSpent = (int) (1000*(t2 - t1) / ( (double) CLOCKS_PER_SEC));
  int delay = msPerFrame - msSpent;
  if(delay > 0) {
    SDL_Delay(delay);
  }

  if(!menuMode && board.getTiles().size() == 0) switchToMenuMode();
}

void Application::requestEnd() {
  haveFinished = true;
}

void Application::end() {
  haveFinished = true;
  SDL_FreeSurface(screen);
  SDL_DestroyWindow(window);
}

void Application::menuNavigate(Menu *menu) {
  if(menu == NULL)
    menuStack.pop();
  else
    menuStack.push(menu);
}

void Application::switchToMenuMode() {
  menuMode = true;
}

void Application::switchToGameMode() {
  menuMode = false;
 
  char lvl[4];
  sprintf(lvl, "%d", Configuration::level);
  std::string level(lvl);
  std::string levelpath = "levels/level" + level + ".txt";

  board.resetBoard(levelpath);
  gamePane -> reset();
}

