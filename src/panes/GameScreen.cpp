#include<panes/GameScreen.h>
#include<model/Board.h>
#include<model/Ball.h>
#include<model/Paddle.h>
#include<SDL.h>
#include<Global.h>

void GameScreen::loadPaddleSprites(SDL_Surface *spritesheet) {
  int spriteHeight = 22;
  int rows = 8;
  paddleSprites.resize(rows);
  for(int i = 0, paddleWidth = 128; i < rows; i++) {
    paddleSprites[i] = SDL_CreateRGBSurface(0, paddleWidth, spriteHeight, 32, 0, 0, 0, 0);
    SDL_Rect r;
    r.x = i*spriteHeight;
    r.y = 0;
    r.w = paddleWidth;
    r.h = spriteHeight;
    SDL_BlitSurface(spritesheet, &r, paddleSprites[i], nullptr);
    SDL_SetColorKey(paddleSprites[i], SDL_TRUE, SDL_MapRGB(paddleSprites[i] -> format, 0xff, 0, 0xff));
    if(i < 2) paddleWidth -= 4;
    else if(i < 6) paddleWidth -= 8;
    else paddleWidth -= 12;
  }
}

void GameScreen::loadSpritesFromGrid(SDL_Surface *spritesheet, 
				     int firstSpriteX, int firstSpriteY,
				     int spriteWidth, int spriteHeight,
				     int horizontalGap, int verticalGap,
				     int rows, int columns,
				     std::vector<SDL_Surface *> &spriteArray) {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      spriteArray.push_back(SDL_CreateRGBSurface(0, 
						 spriteWidth,
						 spriteHeight,
						 32, 0, 0, 0, 0));
      int idx = spriteArray.size()-1;
      SDL_Rect r;
      r.x = firstSpriteX + j*(spriteWidth + horizontalGap);
      r.y = firstSpriteY + i*(spriteHeight + verticalGap);
      r.w = spriteWidth;
      r.h = spriteHeight;
      SDL_BlitSurface(spritesheet, &r, spriteArray[idx], nullptr);
      SDL_SetColorKey(spriteArray[idx], SDL_TRUE, SDL_MapRGB(spriteArray[idx] -> format, 0xff, 0, 0xff));
    }
  }
}


void GameScreen::loadBallSprites(SDL_Surface *spritesheet) {
  loadSpritesFromGrid(spritesheet, 129, 67, 10, 10, 0, 0, 1, 5, ballSprites);
}

void GameScreen::loadPowerupSprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> powerupSprites;
  loadSpritesFromGrid(spritesheet, 129, 165, 44, 22, 0, 2, 7, 8, powerupSprites);
  powerupAnimator.loadSprites(powerupSprites);
}

void GameScreen::loadTileSprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> tileSprites;
  loadSpritesFromGrid(spritesheet, 129, 1, 44, 22, 0, 0, 3, 3, tileSprites);
  loadSpritesFromGrid(spritesheet, 129, 77, 44, 22, 0, 0, 4, 5, tileSprites);
  tileAnimator.loadSprites(tileSprites);
}

GameScreen::GameScreen(Board &newBoard) : board(newBoard), tileAnimator(newBoard.getTiles()), powerupAnimator(newBoard.getPowerups()) {
  width = GAME_SCREEN_WIDTH;
  height = GAME_SCREEN_HEIGHT;
  board.addMonitor(&tileAnimator);
  board.addMonitor(&powerupAnimator);
  SDL_Surface *spritesheet = SDL_LoadBMP("./res/sprites/sprites.bmp");
  loadTileSprites(spritesheet);
  loadBallSprites(spritesheet);
  loadPaddleSprites(spritesheet);
  loadPowerupSprites(spritesheet);
  SDL_FreeSurface(spritesheet);
}

void GameScreen::drawBackground(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  r.x = baseX; 
  r.y = baseY;
  r.w = GAME_SCREEN_WIDTH;
  r.h = GAME_SCREEN_HEIGHT;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));
}

void GameScreen::drawShadows(SDL_Surface *target, int baseX, int baseY) {
  tileAnimator.drawShadows(target, baseX, baseY);
  for(int i = 0; i < board.numBalls(); i++) {
    Ball & ball = board.getBall(i);
    SDL_Rect r;
    r.x = ball.getX() + baseX + 5;
    r.y = ball.getY() + baseY + 10;
    SDL_BlitSurface(ballSprites[4], nullptr, target, &r);
  }
}

void GameScreen::drawBall(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < board.numBalls(); i++) {
    Ball &ball = board.getBall(i);
    SDL_Rect r;
    r.x = ball.getX() + baseX;
    r.y = ball.getY() + baseY;
    SDL_BlitSurface(ballSprites[0], nullptr, target, &r);
  }
}

void GameScreen::drawTiles(SDL_Surface *target, int baseX, int baseY) {
  tileAnimator.drawTiles(target, baseX, baseY);
}

void GameScreen::drawPowerups(SDL_Surface *target, int baseX, int baseY) {
  powerupAnimator.drawPowerups(target, baseX, baseY);
}

void GameScreen::drawPaddle(SDL_Surface *target, int baseX, int baseY) {
  Paddle &player = board.getPaddle();
  SDL_Rect r;
  r.x = player.getX() + baseX;
  r.y = player.getY() + baseY;
  r.w = player.getWidth();
  r.h = player.getHeight();
  SDL_BlitSurface(paddleSprites[0], nullptr, target, &r);
}

void GameScreen::drawYourself(SDL_Surface *target, int baseX, int baseY) {
  drawBackground(target, baseX, baseY);
  drawShadows(target, baseX, baseY);
  drawTiles(target, baseX, baseY);
  drawPowerups(target, baseX, baseY);
  drawBall(target, baseX, baseY);
  drawPaddle(target, baseX, baseY);
}
