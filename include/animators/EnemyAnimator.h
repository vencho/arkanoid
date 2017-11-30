#ifndef ENEMY_ANIMATOR_INCLUDED
#define ENEMY_ANIMATOR_INCLUDED
#include<model/Enemy.h>
#include<vector>
#include<SDL.h>
#include<unordered_map>
 
class EnemyAnimator {
 private:
  std::vector<Enemy> &enemies;
  std::vector<SDL_Surface *> enemySprites;
  const static int framesPerSprite = 3;
  std::unordered_map<int, int> frameCounter;
  void incrementAll();
 public:
  EnemyAnimator(std::vector<Enemy> &tiles);
  void loadSprites(SDL_Surface *spritesheet);
  void draw(SDL_Surface *target, int baseX, int baseY);
};
#endif
