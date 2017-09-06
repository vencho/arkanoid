#ifndef GAME_PANE_H_INCLUDED
#define GAME_PANE_H_INCLUDED
#include<DrawablePaneComposition.h>
class Board;
class GamePane : public DrawablePaneComposition {
 public:
  GamePane(Board *board);
};
#endif

