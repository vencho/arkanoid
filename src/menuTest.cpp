#include<Global.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<ctime>

#include<Menu.h>
#include<MenuPane.h>
#include<BasicMenuItem.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  
  SDL_Window *window = SDL_CreateWindow("Arkanoid menu test", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					640,
					480,
					0);
  SDL_Surface *screen = SDL_GetWindowSurface(window);



  bool quit = false;
  

  Menu mainMenu("my main menu");
  mainMenu.addMenuItem(new BasicMenuItem("Option 1", true));
  mainMenu.addMenuItem(new BasicMenuItem("Option 2", false));
  mainMenu.addMenuItem(new BasicMenuItem("Option 3", false));
  
  MenuPane pane(mainMenu, 640, 480);
  pane.draw(screen, 0, 0);
  SDL_UpdateWindowSurface(window);

  SDL_Delay(3000);

  
  TTF_Quit();
  SDL_Quit();
  return 0;
}
