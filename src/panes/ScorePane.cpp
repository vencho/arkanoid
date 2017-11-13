#include<panes/ScorePane.h>

ScorePane::ScorePane(Board &board) : board(board) {
  board.addDeathMonitor(this);
  board.addTileDestructionMonitor(this);
  this -> width = SCORE_PANE_WIDTH;
  this -> height = SCORE_PANE_HEIGHT;
  font = TTF_OpenFont("./res/fonts/Pacifico.ttf", 20);
  textcolor = {0, 0, 255};
  resetPane();
}

void ScorePane::resetPane() {
  tilesTotal = board.numTiles();
  tilesLeft = tilesTotal;
  deaths = 0;
}

void ScorePane::notifyDied() {
  deaths++;
}

void ScorePane::notifyTileHit(int id) {

}

void ScorePane::notifyTileDestroyed(int id) {
  tilesLeft--;
}


void ScorePane::drawYourself(SDL_Surface *target, int baseX, int baseY) {
  char txt[64];
  sprintf(txt, "Deaths: %d         Tiles: %d / %d\n", deaths, tilesTotal - tilesLeft, tilesTotal);
  SDL_Surface *textsurface = TTF_RenderText_Solid(font, txt, textcolor);
  SDL_Rect r;

  r.x = baseX; 
  r.y = baseY;
  r.w = SCORE_PANE_WIDTH;
  r.h = SCORE_PANE_HEIGHT;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0, 0, 0));

  r.x = baseX;
  r.y = baseY;
  SDL_BlitSurface(textsurface, NULL, target, &r);
  SDL_FreeSurface(textsurface);
}

