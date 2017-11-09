#ifndef PADDLE_DRAWER_H_DEFINED
#define PADDLE_DRAWER_H

#include<model/Paddle.h>
#include<SDL.h>

class PaddleDrawer {
 private:
  SDL_Surface *paddleSprites[8];
  
 public:
  PaddleDrawer();
  void draw(SDL_Surface *target, int baseX, int baseY, Paddle &paddle);
};

#endif
