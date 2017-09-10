#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED
#include<SDL.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>

class GameScreen : public DrawablePane {
 private:
  Board &board;
  int colours[6] = { 0, 0x00ff00, 0xffff00, 0xff0000, 0x0000ff, 0x000000 };
  
 public:
  GameScreen(Board &newBoard);
  SDL_Surface * draw();
  void handleInput(SDL_KeyboardEvent *e);
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
  virtual void tick();

};


#endif
