#ifndef BORDER_ANIMATOR_H_DEFINED
#define BORDER_ANIMATOR_H_DEFINED
#include<SDL.h>
#include<model/Board.h>

class BorderAnimator {
 private:
  const Board &board;
  SDL_Surface *shortHorizontalPipeSprite, *longHorizontalPipeSprite;
  SDL_Surface *leftAnglePipeSprite, *rightAnglePipeSprite; 
  SDL_Surface *leftVerticalPipeSprite, *rightVerticalPipeSprite;
  std::vector<SDL_Surface *> gateSprites;

  std::vector<SDL_Surface *> topPipes, leftPipes, rightPipes;

  int chooseGateSprite(int x);
  void selectGateSprites();

 public:
  BorderAnimator(const Board &board);
  void loadSprites(SDL_Surface *spritesheet);
  void drawBackground(SDL_Surface *target, int baseX, int baseY);
  void drawBorders(SDL_Surface *target, int baseX, int baseY);
  void reset();
};
#endif
