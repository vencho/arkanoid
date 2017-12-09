#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED
#include<SDL.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>
#include<animators/ExplosionAnimator.h>
#include<animators/BorderAnimator.h>

#include<../src/animators/Animator.cpp>

class GameScreen : public DrawablePane {
 private:
  Animator<Powerup> powerupAnimator;
  Animator<Ball> ballAnimator;
  Animator<Enemy> enemyAnimator;
  Animator<Tile> tileAnimator;
  Animator<Paddle> paddleAnimator;
  Animator<Bullet> bulletAnimator;
  BorderAnimator borderAnimator;
  ExplosionAnimator explosionAnimator;

 public:
  GameScreen(Board &board);
  virtual void reset();
  const static int borderSize = 18;
  const static int gameScreenWidth = Board::playAreaWidth + 2*borderSize;
  const static int gameScreenHeight = Board::playAreaHeight + borderSize;
  const static int shadowOffsetX = 5;
  const static int shadowOffsetY = 10;

 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
};
#endif
