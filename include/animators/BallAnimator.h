#ifndef BALL_ANIMATOR_H_DEFINED
#define BALL_ANIMATOR_H

#include<model/Ball.h>
#include<SDL.h>
#include<vector>

class BallAnimator {
 private:
  std::vector<SDL_Surface *> ballSprites;
  SDL_Surface *ballShadow;
  std::vector<Ball> &balls;
  
 public:
  BallAnimator(std::vector<Ball> &balls);
  void drawBalls(SDL_Surface *target, int baseX, int baseY);
  void drawShadows(SDL_Surface *target, int baseX, int baseY);
  void loadSprites(std::vector<SDL_Surface *> &sprites);
};

#endif
