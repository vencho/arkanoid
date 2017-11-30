#ifndef BULLET_ANIMATOR_H_DEFINED
#define BULLET_ANIMATOR_H_DEFINED
#include<model/Board.h>
#include<SDL.h>
class BulletAnimator {
 private:
  Board &board;
  SDL_Surface *bulletSprite;
 public:
  BulletAnimator(Board &board);
  void loadSprites(SDL_Surface *spritesheet);
  void draw(SDL_Surface *target, int baseX, int baseY);
};
#endif
