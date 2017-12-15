#include<panes/ScorePane.h>

ScorePane::ScorePane(Board &board) : board(board) {
  board.addMonitor(this);
  this -> width = scorePaneWidth;
  this -> height = scorePaneHeight;
  font = TTF_OpenFont("./res/fonts/Pacifico.ttf", 20);
  textcolor = {0, 0, 255};
  reset();
}

void ScorePane::reset() {
  tilesTotal = board.getTiles().size();
  tilesLeft = tilesTotal;
  deaths = 0;
}

void ScorePane::notifyDied() {
  deaths++;
}

void ScorePane::notifyLeaves(const Tile &tile) {
  tilesLeft--;
}

void ScorePane::drawYourself(SDL_Surface *target, int baseX, int baseY) {
  char txt[64];
  sprintf(txt, "Deaths: %d         Tiles: %d / %d\n", deaths, tilesTotal - tilesLeft, tilesTotal);
  SDL_Surface *textsurface = TTF_RenderText_Solid(font, txt, textcolor);
  SDL_Rect r;

  r.x = baseX; 
  r.y = baseY;
  r.w = scorePaneWidth;
  r.h = scorePaneHeight;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0, 0, 0));

  r.x = baseX;
  r.y = baseY;
  SDL_BlitSurface(textsurface, NULL, target, &r);
  SDL_FreeSurface(textsurface);
}

