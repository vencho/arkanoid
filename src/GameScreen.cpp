#include<GameScreen.h>
#include<Board.h>
#include<Ball.h>
#include<Paddle.h>
#include<SDL.h>
#include<Global.h>

GameScreen::GameScreen(Board &newBoard) : board(newBoard) {
  width = GAME_SCREEN_WIDTH;
  height = GAME_SCREEN_HEIGHT;
}


void GameScreen::handleInput(SDL_KeyboardEvent *e) {
}

void GameScreen::tick() {
  board.tick();
}

void GameScreen::draw(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  
  // Draw background
  r.x = baseX; 
  r.y = baseY;
  r.w = GAME_SCREEN_WIDTH;
  r.h = GAME_SCREEN_HEIGHT;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));

  // Draw the ball
  Ball &ball = board.getBall(0);
  r.x = ball.getX();
  r.y = ball.getY();
  r.w = ball.getWidth();
  r.h = ball.getHeight();
  if(r.y + r.h > height) r.h = height - r.y;
  r.x += baseX;
  r.y += baseY;
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
