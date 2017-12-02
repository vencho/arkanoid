#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED
#include<SDL.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>
#include<animators/TileAnimator.h>
#include<animators/PowerupAnimator.h>
#include<animators/BallAnimator.h>
#include<animators/EnemyAnimator.h>
#include<animators/ExplosionAnimator.h>
#include<animators/PaddleAnimator.h>
#include<animators/BorderAnimator.h>
#include<animators/BulletAnimator.h>

class GameScreen : public DrawablePane {
 private:
  TileAnimator tileAnimator;
  PowerupAnimator powerupAnimator;
  BallAnimator ballAnimator;
  EnemyAnimator enemyAnimator;
  ExplosionAnimator explosionAnimator;
  PaddleAnimator paddleAnimator;
  BorderAnimator borderAnimator;
  BulletAnimator bulletAnimator;

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
