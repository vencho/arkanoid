#ifndef TILE_DRAWER_H_DEFINED
#define TILE_DRAWER_H

#include<model/Tile.h>
#include<SDL.h>

class TileDrawer {
 private:
  SDL_Surface *tileSprites[8];
  const int shadowExtentRight = 12;
  const int shadowExtentDown = 12;
 public:
  TileDrawer();
  void draw(SDL_Surface *target, int baseX, int baseY, Tile &tile);
};

#endif
