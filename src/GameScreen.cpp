#include<GameScreen.h>
#include<Board.h>
#include<Ball.h>
#include<Paddle.h>

GameScreen::GameScreen(Board &newBoard) : DrawablePane(), board(newBoard) {
  width = MAXX;
  height = MAXY;
}



void GameScreen::draw(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  
  // Draw background
  r.x = baseX; 
  r.y = baseY;
  r.w = MAXX;
  r.h = MAXY;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));

  // Draw the ball
  Ball &ball = board.getBall(0);
  r.x = ball.getX() + baseX;
  r.y = ball.getY() + baseY;
  r.w = ball.getWidth();
  r.h = ball.getHeight();
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0, 255, 0));

  // Iterate over the tiles and draw each
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

  // Draw the paddle
  Paddle &player = board.getPaddle();
  r.x = player.getX() + baseX;
  r.y = player.getY() + baseY;
  r.w = player.getWidth();
  r.h = player.getHeight();
  SDL_FillRect(target, &r, SDL_MapRGB(target -> format, 0xff, 0x12, 0x34));
}
