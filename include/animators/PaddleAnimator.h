#ifndef PADDLE_ANIMATOR_H_DEFINED
#define PADDLE_ANIMATOR_H_DEFINED
#include<model/Board.h>
#include<SDL.h>

class PaddleAnimator {
 private:
  const Board &board;
  std::vector<SDL_Surface *> paddleSprites;
 public:
  PaddleAnimator(const Board &board);
  void loadSprites(SDL_Surface *spritesheet);
  void draw(SDL_Surface *target, int baseX, int baseY);
  void reset();
};
#endif
