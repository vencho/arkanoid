#include<animators/PaddleAnimator.h>

PaddleAnimator::PaddleAnimator(Board &board) : board(board) { }

void PaddleAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  Paddle &player = board.getPaddle();
  SDL_Rect r;
  r.x = player.getX() + baseX;
  r.y = player.getY() + baseY;
  SDL_BlitSurface(paddleSprites[7-player.getLength()], nullptr, target, &r);
}

void PaddleAnimator::loadSprites(SDL_Surface *spritesheet) {
  int spriteHeight = 22;
  int rows = 8;
  paddleSprites.resize(rows);
  for(int i = 0, paddleWidth = 128; i < rows; i++) {
    paddleSprites[i] = SDL_CreateRGBSurface(0, paddleWidth, spriteHeight, 32, 0, 0, 0, 0);
    SDL_Rect r;
    r.x = 0;
    r.y = i*spriteHeight;
    r.w = paddleWidth;
    r.h = spriteHeight;
    SDL_BlitSurface(spritesheet, &r, paddleSprites[i], nullptr);
    SDL_SetColorKey(paddleSprites[i], SDL_TRUE, SDL_MapRGB(paddleSprites[i] -> format, 0xff, 0, 0xff));
    if(i < 3) paddleWidth -= 4;
    else if(i < 6) paddleWidth -= 8;
    else paddleWidth -= 12;
  }
}
