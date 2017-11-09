#include<drawers/PaddleDrawer.h>
#include<SDL.h>

PaddleDrawer::PaddleDrawer() {
  SDL_Surface *spritesheet = SDL_LoadBMP("./res/sprites/sprites.bmp");
  int paddleHeight = 22;
  for(int i = 0, paddleWidth = 128; i < 8; i++) {
    paddleSprites[i] = SDL_CreateRGBSurface(0, paddleWidth, paddleHeight, 32, 0, 0, 0, 0);
    SDL_Rect r;
    r.x = i*paddleHeight;
    r.y = 0;
    r.w = paddleWidth;
    r.h = paddleHeight;
    SDL_BlitSurface(spritesheet, &r, paddleSprites[i], nullptr);
    SDL_SetColorKey(paddleSprites[i], SDL_TRUE, SDL_MapRGB(paddleSprites[i] -> format, 0xff, 0, 0xff));
    if(i < 2) paddleWidth -= 4;
    else if(i < 6) paddleWidth -= 8;
    else paddleWidth -= 12;
  }
  SDL_FreeSurface(spritesheet);
}

void PaddleDrawer::draw(SDL_Surface *target, int baseX, int baseY, Paddle &player) {
  SDL_Rect r;
  r.x = player.getX() + baseX;
  r.y = player.getY() + baseY;
  r.w = player.getWidth();
  r.h = player.getHeight();
  SDL_BlitSurface(paddleSprites[0], nullptr, target, &r);
}
