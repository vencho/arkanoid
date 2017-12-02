#ifndef POWERUP_ANIMATOR_H_INCLUDED
#define POWERUP_ANIMATOR_H_INCLUDED

#include<SDL.h>
#include<model/Powerup.h>
#include<vector>
#include<unordered_map>
#include<observers/GameEventMonitor.h>

class PowerupAnimator : public GameEventMonitor {
 private:
  std::vector<std::vector<SDL_Surface *>> powerupSprites;
  const std::vector<Powerup> &powerups;
  std::unordered_map<int, int> whichFrame;
  std::unordered_map<char, int> whichRow;
  void incrementAll();

  const static int framesPerSprite = 5;
 public:
  PowerupAnimator(const std::vector<Powerup> &powerups);
  void loadSprites(SDL_Surface *spritesheet);

  void draw(SDL_Surface *target, int baseX, int baseY);
  virtual void notifyPowerupDestroyed(int id);
  void reset();
};

#endif
