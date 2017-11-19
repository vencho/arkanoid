#ifndef TILE_ANIMATOR_H_INCLUDED
#define TILE_ANIMATOR_H_INCLUDED

#include<model/Tile.h>
#include<observers/GameEventMonitor.h>
#include<SDL.h>
#include<vector>
#include<unordered_map>

class TileAnimator : public GameEventMonitor {
 private:
  std::vector<SDL_Surface *> normalTiles;
  std::vector<SDL_Surface *> silverTiles;
  std::vector<SDL_Surface *> goldenTiles;
  SDL_Surface *shadow;
  std::vector<Tile> &tiles;
  std::unordered_map<int, int> framesShining;
  void incrementAllFramesShining();

 public:
  TileAnimator(std::vector<Tile> &tiles);
  void loadSprites(std::vector<SDL_Surface *> &sprites);
  void drawShadows(SDL_Surface *target, int baseX, int baseY);
  void drawTiles(SDL_Surface *target, int baseX, int baseY);
  virtual void notifyTileDestroyed(int id);
  virtual void notifyTileHit(int id);
};

#endif
