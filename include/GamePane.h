#ifndef GAME_PANE_H_INCLUDED
#define GAME_PANE_H_INCLUDED
#include<DrawablePaneComposition.h>
class Board;
class GameScreen;
class ScorePane;
class GamePane : public DrawablePaneComposition {
 private:
  GameScreen *gs;
  ScorePane *sp;
 public:
  GamePane(Board *board);
  ~GamePane();
  virtual void tick();
};
#endif

