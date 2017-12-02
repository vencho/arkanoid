#include<animators/BallAnimator.h>
#include<panes/GameScreen.h>
#include<SpriteUtils.h>

BallAnimator::BallAnimator(const std::vector<Ball> &balls) : balls(balls) {

}

void BallAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < balls.size(); i++) {
    const Ball &ball = balls[i];
    SDL_Rect r;
    r.x = ball.getX() + baseX;
    r.y = ball.getY() + baseY;
    SDL_BlitSurface(ballSprites[0], nullptr, target, &r);
  }
}

void BallAnimator::drawShadows(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < balls.size(); i++) {
    const Ball &ball = balls[i];
    SDL_Rect r;
    r.x = ball.getX() + baseX + GameScreen::shadowOffsetX;
    r.y = ball.getY() + baseY + GameScreen::shadowOffsetY;
    SDL_BlitSurface(ballShadow, nullptr, target, &r);
  }
}

void BallAnimator::loadSprites(SDL_Surface *spritesheet) {
  SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 67, 10, 10, 0, 0, 1, 5, 10, 10, ballSprites);
  ballShadow = ballSprites[4];
  ballSprites.resize(4);
}

void BallAnimator::reset() {

}
