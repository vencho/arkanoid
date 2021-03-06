#ifndef SCOREPANE_H_DEFINED
#define SCOREPANE_H_DEFINED

#include<SDL.h>
#include<SDL_ttf.h>
#include<panes/DrawablePane.h>
#include<panes/GameScreen.h>
#include<model/Board.h>
#include<observers/GameEventMonitor.h>

class ScorePane : public DrawablePane, public GameEventMonitor {
 private:
  int deaths, tilesLeft, tilesTotal;
  TTF_Font *font;
  SDL_Color textcolor;
  const Board &board;
 public:
  const static int scorePaneWidth = GameScreen::gameScreenWidth;
  const static int scorePaneHeight = 40;
  ScorePane(Board &B);
  virtual void notifyDied();
  virtual void reset();
  virtual void notifyLeaves(const Tile &tile);
 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
};

#endif
