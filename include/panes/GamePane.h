#ifndef GAME_PANE_H_INCLUDED
#define GAME_PANE_H_INCLUDED
#include<panes/DrawablePaneComposition.h>
class Board;
class GameScreen;
class ScorePane;
class GamePane : public DrawablePaneComposition {
 public:
  GamePane(Board &board);
  virtual void tick();
  void resetPane();

};
#endif

