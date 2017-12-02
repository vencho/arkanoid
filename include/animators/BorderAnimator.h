#ifndef BORDER_ANIMATOR_H_DEFINED
#define BORDER_ANIMATOR_H_DEFINED
#include<SDL.h>
#include<model/Board.h>

class BorderAnimator {
 private:
  const Board &board;
  SDL_Surface *shortHorizontalPipeSprite, *longHorizontalPipeSprite, *leftAnglePipeSprite, *rightAnglePipeSprite, *verticalPipeSprite;
  std::vector<SDL_Surface *> gateSprites;
  void loadBorderSprites(SDL_Surface *spritesheet);
  
 public:
  BorderAnimator(const Board &board);
  void loadSprites(SDL_Surface *spritesheet);
  void drawBackground(SDL_Surface *target, int baseX, int baseY);
  void drawBorders(SDL_Surface *target, int baseX, int baseY);
  void reset();
};
#endif
