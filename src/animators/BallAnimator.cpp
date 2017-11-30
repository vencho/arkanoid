#include<animators/BallAnimator.h>
#include<SpriteUtils.h>

BallAnimator::BallAnimator(std::vector<Ball> &balls) : balls(balls) {

}

void BallAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < balls.size(); i++) {
    Ball &ball = balls[i];
    SDL_Rect r;
    r.x = ball.getX() + baseX;
    r.y = ball.getY() + baseY;
    SDL_BlitSurface(ballSprites[0], nullptr, target, &r);
  }
}

void BallAnimator::drawShadows(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < balls.size(); i++) {
    Ball & ball = balls[i];
    SDL_Rect r;
    r.x = ball.getX() + baseX + SHADOW_OFFSET_X;
    r.y = ball.getY() + baseY + SHADOW_OFFSET_Y;
    SDL_BlitSurface(ballShadow, nullptr, target, &r);
  }
}

void BallAnimator::loadSprites(SDL_Surface *spritesheet) {
  SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 67, 10, 10, 0, 0, 1, 5, 10, 10, ballSprites);
  ballShadow = ballSprites[4];
  ballSprites.resize(4);
}

