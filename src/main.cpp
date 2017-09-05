#include<Board.h>
#include<Global.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<GameScreen.h>
#include<ScorePane.h>
#include<ctime>
#include<DrawablePaneComposition.h>
#include<BasicMenuItem.h>
#include<Menu.h>
#include<MenuItem.h>
#include<MenuPane.h>
#include<Application.h>

int main() {
  Application arkanoid;

  arkanoid.start();
  while(!arkanoid.isFinished()) {
    arkanoid.tick();
  }

  /*

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  
  SDL_Window *window = SDL_CreateWindow("Arkanoid", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH,
					SCREEN_HEIGHT,
					0);
  SDL_Surface *screen = SDL_GetWindowSurface(window);

  */

  /*
  clock_t t1, t2;
  double secondsspent;
  clock();

  Menu mainMenu("Main menu");
  mainMenu.addMenuItem(new BasicMenuItem("New game", true));
  mainMenu.addMenuItem(new BasicMenuItem("Options", false));
  mainMenu.addMenuItem(new BasicMenuItem("Quit", false));

  Menu optionsMenu("Options");
  optionsMenu.addMenuItem(new BasicMenuItem("Example", true));
  optionsMenu.addMenuItem(new BasicMenuItem("Back", false));
  
  
  MenuPane mainMenuPane(mainMenu, SCREEN_WIDTH, SCREEN_HEIGHT);
  MenuPane optionsMenuPane(optionsMenu, SCREEN_WIDTH, SCREEN_HEIGHT);

  bool quit = false;
  while(!quit) {

    t1 = clock();

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_KEYDOWN) {
	pane.handleInput(&(e.key));
      }
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_Q]) quit = true;

    pane.draw(screen, 0, 0);
    SDL_UpdateWindowSurface(window);
    
    t2 = clock();
    double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;
    int delay = (int)(1000*(SPF - secondsspent));
    SDL_Delay(delay);
  }

  */

  /*
  Board B(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "levels/level1.txt");
  GameScreen gameScreen(B);
  ScorePane scorePane(B);
  DrawablePaneComposition bothPanes(true);
  
  bothPanes.addPane(&scorePane);
  bothPanes.addPane(&gameScreen);
  
  bool quit = false;

  SDL_Event e;
  while(!quit) {

    t1 = clock();

    while(SDL_PollEvent(&e)) { }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    Uint8 leftPressed = currentKeyStates[SDL_SCANCODE_A];
    Uint8 rightPressed = currentKeyStates[SDL_SCANCODE_D];
    int dx;
    if( (leftPressed ^ rightPressed) == 0 ) { dx = 0; } 
    else if(leftPressed) { dx = -1; } 
    else { dx = 1; }
    B.getPaddle().setVelocity(dx*PADDLE_SPEED, 0);

    if(currentKeyStates[SDL_SCANCODE_Q]) quit = true;

    if(currentKeyStates[SDL_SCANCODE_W]) B.initialiseBalls();

    B.tick();
    bothPanes.draw(screen, 0, 0);
    SDL_UpdateWindowSurface(window);
    
    t2 = clock();
    double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;
    int delay = (int)(1000*(SPF - secondsspent));
    SDL_Delay(delay);
  }
  */

  /*
  TTF_Quit();
  SDL_Quit();
  */
  return 0;
}
