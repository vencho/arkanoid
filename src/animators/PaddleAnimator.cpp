#include<animators/PaddleAnimator.h>
#include<SpriteUtils.h>

const int PaddleAnimator::paddleSpriteLength[8] = { 80, 92, 100, 108, 116, 120, 124, 128 };

PaddleAnimator::PaddleAnimator(const Board &board) : board(board) { }

void PaddleAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  const Paddle &player = board.getPaddle();
  SDL_Rect r;
  r.x = player.getX() + baseX;
  r.y = player.getY() + baseY;
  SDL_BlitSurface(paddleSprites[7-player.getLength()], nullptr, target, &r);
}

void PaddleAnimator::loadSprites(SDL_Surface *spritesheet) {
  paddleSprites.resize(8);
  for(int i = 0; i < 8; i++) {
    paddleSprites[i] = SpriteUtils::loadSingleSprite(spritesheet, 0, 22*i, paddleSpriteLength[7-i], 22, 
						     Paddle::paddlePhysicalLength[7-i], 
						     Paddle::paddlePhysicalHeight);
  }
}

void PaddleAnimator::reset() {
  
}
