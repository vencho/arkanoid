#ifndef BALL_ANIMATOR_H_DEFINED
#define BALL_ANIMATOR_H

#include<model/Ball.h>
#include<SDL.h>
#include<vector>

class BallAnimator {
 private:
  std::vector<SDL_Surface *> ballSprites;
  SDL_Surface *ballShadow;
  const std::vector<Ball> &balls;
  
 public:
  BallAnimator(const std::vector<Ball> &balls);
  void draw(SDL_Surface *target, int baseX, int baseY);
  void drawShadows(SDL_Surface *target, int baseX, int baseY);
  void loadSprites(SDL_Surface *spritesheet);
  void reset();
};

#endif
