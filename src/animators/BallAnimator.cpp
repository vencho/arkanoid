#include<animators/BallAnimator.h>


BallAnimator::BallAnimator(std::vector<Ball> &balls) : balls(balls) {

}

void BallAnimator::drawBalls(SDL_Surface *target, int baseX, int baseY) {
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


void BallAnimator::loadSprites(std::vector<SDL_Surface *> &sprites) {
  ballSprites.resize(4);
  for(int i = 0; i < 4; i++) ballSprites[i] = sprites[i];
  ballShadow = sprites[4];
}

