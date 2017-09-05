#include<Application.h>
#include<MenuPane.h>
#include<BasicMenuItem.h>
#include<Menu.h>
#include<Global.h>
#include<ChangePaneCommand.h>
#include<Board.h>
#include<DrawablePaneComposition.h>
#include<GameScreen.h>
#include<ScorePane.h>

Application::Application() {
  ended = true;
}

bool Application::isFinished() {
  return ended;
}

void Application::start() {
  ended = false;
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  window = SDL_CreateWindow("Arkanoid", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH,
					SCREEN_HEIGHT,
					0);
  screen = SDL_GetWindowSurface(window);
  Menu *main = new Menu("Main menu");
  BasicMenuItem *newgameitem, *optionsitem, *quititem;
  newgameitem = new BasicMenuItem("New game", true);
  optionsitem = new BasicMenuItem("Options", false);
  quititem = new BasicMenuItem("Quit", false);
  main -> addMenuItem(newgameitem);
  main -> addMenuItem(optionsitem); 
  main -> addMenuItem(quititem);

  Menu *options = new Menu("Options");
  BasicMenuItem *exampleitem, *backitem;
  exampleitem = new BasicMenuItem("Example", true);
  backitem = new BasicMenuItem("Back", false);
  options -> addMenuItem(exampleitem);
  options -> addMenuItem(backitem);



  mainMenu = new MenuPane(*main, SCREEN_WIDTH, SCREEN_HEIGHT);
  optionsMenu = new MenuPane(*options, SCREEN_WIDTH, SCREEN_HEIGHT);
  gameScreen = NULL;

  Board *board = new Board(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "levels/level1.txt");
  GameScreen *gs = new GameScreen(*board);
  ScorePane *sp = new ScorePane(*board);
  DrawablePaneComposition *bothPanes = new DrawablePaneComposition(true);
  
  bothPanes -> addPane(sp);
  bothPanes -> addPane(gs);
  gameScreen = bothPanes;

  ChangePaneCommand *toOptions = new ChangePaneCommand(*this, optionsMenu);
  optionsitem -> addReaction(SDLK_RETURN, toOptions);

  ChangePaneCommand *toMain = new ChangePaneCommand(*this, mainMenu);
  backitem -> addReaction(SDLK_RETURN, toMain);

  ChangePaneCommand *toGameScreen = new ChangePaneCommand(*this, gameScreen);
  newgameitem -> addReaction(SDLK_RETURN, toGameScreen);
  
  currentDisplay = mainMenu;
  
  ended = false;
}

void Application::setActivePane(DrawablePane *pane) {

  SDL_Rect r;
  r.x = 0; 
  r.y = 0;
  r.w = SCREEN_WIDTH;
  r.h = SCREEN_HEIGHT;
  SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0,0,0));
  currentDisplay = pane;
}


void Application::handleInput() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) { 
    if(e.type != SDL_KEYDOWN) continue;
    if(e.key.keysym.sym == SDLK_q) { end(); return; }
    if(currentDisplay) currentDisplay -> handleInput(& (e.key));
  }
}

void Application::tick() {
  if(isFinished()) return;

  double t1, t2;
  t1 = clock();

  handleInput();
  if(isFinished()) return;
  if(currentDisplay) currentDisplay -> draw(screen, 0, 0);
  SDL_UpdateWindowSurface(window);

  t2 = clock();
  double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;
  int delay = (int)(1000*(SPF - secondsspent));
  SDL_Delay(delay);
}

void Application::end() {
  ended = true;
  if(mainMenu) delete mainMenu;
  if(optionsMenu) delete optionsMenu;
  if(gameScreen) delete gameScreen;
  
  SDL_FreeSurface(screen);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}
