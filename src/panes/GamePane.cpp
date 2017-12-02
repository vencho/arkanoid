#include<panes/GamePane.h>
#include<panes/ScorePane.h>
#include<panes/GameScreen.h>
GamePane::GamePane(Board &board) : DrawablePaneComposition(true) {
  std::unique_ptr<ScorePane> sp(new ScorePane(board));
  std::unique_ptr<GameScreen> gs(new GameScreen(board));
  addPane(std::move(sp));
  addPane(std::move(gs));
}

void GamePane::reset() {
  panes[0] -> reset();
  panes[1] -> reset();
}
