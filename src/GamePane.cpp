#include<GamePane.h>
#include<ScorePane.h>
#include<GameScreen.h>
GamePane::GamePane(Board *board) : DrawablePaneComposition(true) {
  gs = new GameScreen(*board);
  sp = new ScorePane(*board);
  addPane(sp);
  addPane(gs);
}

void GamePane::tick() {
  gs -> tick();
}

