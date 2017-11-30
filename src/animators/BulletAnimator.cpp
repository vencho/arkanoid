#include<animators/BulletAnimator.h>
#include<SpriteUtils.h>

BulletAnimator::BulletAnimator(Board &board) : board(board) { }

void BulletAnimator::loadSprites(SDL_Surface *spritesheet) {
  bulletSprite = SpriteUtils::loadSingleSprite(spritesheet, 123, 45, 5, 5); 
}

void BulletAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  std::vector<Bullet> &bullets = board.getBullets();
  for(int i = 0; i < bullets.size(); i++) {
    SDL_Rect r;
    r.x = bullets[i].getX() + baseX;
    r.y = bullets[i].getY() + baseY;
    SDL_BlitSurface(bulletSprite, nullptr, target, &r);
  }
}
