#ifndef EXPLOSION_ANIMATOR_H_INCLUDED
#define EXPLOSION_ANIMATOR_H_INCLUDED
#include<SDL.h>
#include<vector>
#include<model/Enemy.h>
#include<observers/GameEventMonitor.h>

class ExplosionAnimator : public GameEventMonitor {
 private:
  struct explosion {
    int centreX, centreY, ticksSoFar;
    explosion(int x, int y);
  };
  std::vector<SDL_Surface *> explosionSprites;
  std::vector<struct explosion> ongoingExplosions;
  const static int ticksPerSprite = 6;
  void incrementAll();
 public:
  void loadSprites(SDL_Surface *spritesheet);
  void draw(SDL_Surface *target, int baseX, int baseY);
  void addExplosion(int centreX, int centreY);
  virtual void notifyEnemyDestroyed(Enemy &enemy);
  void reset();
};
#endif
