#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED
#include<SDL.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>
#include<drawers/PaddleDrawer.h>
#include<drawers/TileDrawer.h>

class GameScreen : public DrawablePane {
 private:
  Board &board;
  PaddleDrawer paddleDrawer;
  TileDrawer tileDrawer;
  int colours[6] = { 0, 0x00ff00, 0xffff00, 0xff0000, 0x0000ff, 0x000000 };
  void drawBackground(SDL_Surface *target, int baseX, int baseY);
  void drawBall(SDL_Surface *target, int baseX, int baseY);
  void drawTiles(SDL_Surface *target, int baseX, int baseY);
  void drawPaddle(SDL_Surface *target, int baseX, int baseY);
  
 public:
  GameScreen(Board &newBoard);
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
};


#endif
