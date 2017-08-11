#include<View.h>
#include<Board.h>
#include<Ball.h>

View::View(Board &newBoard) : board(newBoard) {
  
}


SDL_Surface *View::draw() {
  SDL_Surface *answer = SDL_CreateRGBSurface(0, MAXX, MAXY, 32, 0, 0, 0, 0);
  SDL_Rect r;
  
  // Draw background
  r.x = r.y = 0;
  r.w = MAXX;
  r.h = MAXY;
  SDL_FillRect(answer, &r, SDL_MapRGB(answer->format, 0xcd, 0xcd, 0xcd));

  // Draw the ball
  Ball &ball = board.getBall(0);
  r.x = ball.getX() - BALL_R;
  r.y = ball.getY() - BALL_R;
  r.w = 2*BALL_R;
  r.h = 2*BALL_R;
  SDL_FillRect(answer, &r, SDL_MapRGB(answer->format, 0, 255, 0));

  // Iterate over the tiles and draw each
  for(int i = 0; i < board.numTiles(); i++) {
    Tile &tile = board.getTile(i);
    r.x = tile.getX();
    r.y = tile.getY();
    r.w = TILE_WIDTH;
    r.h = TILE_HEIGHT;
    int colourcode = colours[tile.getHealth()];
    SDL_FillRect(answer, &r, SDL_MapRGB(answer->format, 
					(colourcode / 65536) % 256, 
					(colourcode / 256) % 256, 
					colourcode % 256));
  }

  // Draw the paddle
  Paddle &player = board.getPaddle();
  r.x = player.getX();
  r.y = player.getY();
  r.w = player.getWidth();
  r.h = player.getHeight();
  SDL_FillRect(answer, &r, SDL_MapRGB(answer -> format, 0xff, 0x12, 0x34));
  
  return answer;
}
