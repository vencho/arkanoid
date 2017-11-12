#ifndef SCOREPANE_H_DEFINED
#define SCOREPANE_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>
#include<observers/DeathMonitor.h>
#include<observers/TileDestructionMonitor.h>

class ScorePane : public DrawablePane, public DeathMonitor, public TileDestructionMonitor {
 private:
  int deaths, tilesLeft, tilesTotal;
  TTF_Font *font;
  SDL_Color textcolor;
  Board &board;
 public:
  ScorePane(Board &B);
  virtual void notifyDied();
  virtual void notifyTileDestroyed();
  void resetPane();
 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
};

#endif
