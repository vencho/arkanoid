#ifndef SCOREPANE_H_DEFINED
#define SCOREPANE_H_DEFINED

#include<DrawablePane.h>
#include<DeathMonitor.h>
#include<TileDestructionMonitor.h>
#include<Board.h>
#include<SDL.h>
#include<SDL_ttf.h>

class ScorePane : public DrawablePane, public DeathMonitor, public TileDestructionMonitor {
 private:
  int deaths, tilesLeft, tilesTotal;
  TTF_Font *font;
  SDL_Color textcolor;

 public:
  ScorePane(Board &B);
  virtual void draw(SDL_Surface *target, int baseX, int baseY);
  virtual void notifyDied();
  virtual void notifyTileDestroyed();
};

#endif
