#include<panes/GameScreen.h>
#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<SDL.h>
#include<Global.h>

GameScreen::GameScreen(Board &newBoard) : board(newBoard), paddleDrawer(), tileDrawer() {
  width = GAME_SCREEN_WIDTH;
  height = GAME_SCREEN_HEIGHT;
}

void GameScreen::drawBackground(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  r.x = baseX; 
  r.y = baseY;
  r.w = GAME_SCREEN_WIDTH;
  r.h = GAME_SCREEN_HEIGHT;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));
}

void GameScreen::drawBall(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  Ball &ball = board.getBall(0);
  r.x = ball.getX();
  r.y = ball.getY();
  r.w = ball.getWidth();
  r.h = ball.getHeight();
  if(r.y + r.h > height) r.h = height - r.y;
  r.x += baseX;
  r.y += baseY;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0, 255, 0));
}

void GameScreen::drawTiles(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < board.numTiles(); i++) {
    Tile &tile = board.getTile(i);
    tileDrawer.draw(target, baseX, baseY, tile);
  }
  /*
  SDL_Rect r;
  for(int i = 0; i < board.numTiles(); i++) {
    Tile &tile = board.getTile(i);
    r.x = tile.getX() + baseX;
    r.y = tile.getY() + baseY;
    r.w = TILE_WIDTH;
    r.h = TILE_HEIGHT;
    int colourcode = colours[tile.getHealth()];
    SDL_FillRect(target, &r, SDL_MapRGB(target->format, 
					(colourcode / 65536) % 256, 
					(colourcode / 256) % 256, 
					colourcode % 256));
  }
  */
}

void GameScreen::drawPaddle(SDL_Surface *target, int baseX, int baseY) {
  paddleDrawer.draw(target, baseX, baseY, board.getPaddle());
}

void GameScreen::draw(SDL_Surface *target, int baseX, int baseY) {
  drawBackground(target, baseX, baseY);
  drawTiles(target, baseX, baseY);
  drawBall(target, baseX, baseY);
  drawPaddle(target, baseX, baseY);
}
