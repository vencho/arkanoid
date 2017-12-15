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
  SDL_Surface *shimmerSprite;
  
  std::vector<SDL_Surface *> gateSprites;
  std::vector<SDL_Surface *> bgSprites;
  int curBgSpriteIdx;
  std::vector<SDL_Surface *> topPipes, leftPipes, rightPipes, rightPipesWithShimmer;

  int chooseGateSprite(int x);
  void selectGateSprites();

 public:
  BorderAnimator(const Board &board);
  void loadSprites(SDL_Surface *spritesheet, SDL_Surface *backgrounds);
  void drawBackground(SDL_Surface *target, int baseX, int baseY);
  void drawBorders(SDL_Surface *target, int baseX, int baseY);
  void reset();
};
#endif
