#include<GamePane.h>
#include<ScorePane.h>
#include<GameScreen.h>
GamePane::GamePane(Board *board) : DrawablePaneComposition(true) {
  GameScreen *gs = new GameScreen(*board);
  ScorePane *sp = new ScorePane(*board);
  addPane(sp);
  addPane(gs);
}


