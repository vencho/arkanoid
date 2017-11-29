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
    r.x = 0;
    r.y = i*spriteHeight;
    r.w = paddleWidth;
    r.h = spriteHeight;
    SDL_BlitSurface(spritesheet, &r, paddleSprites[i], nullptr);
    SDL_SetColorKey(paddleSprites[i], SDL_TRUE, SDL_MapRGB(paddleSprites[i] -> format, 0xff, 0, 0xff));
    if(i < 3) paddleWidth -= 4;
    else if(i < 6) paddleWidth -= 8;
    else paddleWidth -= 12;
  }
}

void GameScreen::loadBorderSprites(SDL_Surface *spritesheet) {
  shortHorizontalPipeSprite = loadSingleSprite(spritesheet, 261, 8, 77, 18);
  longHorizontalPipeSprite = loadSingleSprite(spritesheet, 261, 26, 218, 18);
  leftAnglePipeSprite = loadSingleSprite(spritesheet, 479, 5, 28, 40);
  rightAnglePipeSprite = loadSingleSprite(spritesheet, 479, 47, 28, 40);
  verticalPipeSprite = loadSingleSprite(spritesheet, 490, 96, 18, 94);
  loadSpritesFromGrid(spritesheet, 0, 181, 90, 22, 0, 0, 7, 1, 90, 18, gateSprites);
}

void GameScreen::loadEnemySprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> enemySprites;
  loadSpritesFromGrid(spritesheet, 8, 335, 34, 44, 10, 0, 5, 5, ENEMY_WIDTH, ENEMY_HEIGHT, enemySprites);
  enemyAnimator.loadSprites(enemySprites);
}

void GameScreen::loadBulletSprite(SDL_Surface *spritesheet) {
  bulletSprite = loadSingleSprite(spritesheet, 123, 45, 5, 5); 
}

void GameScreen::loadBallSprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> ballSprites;
  loadSpritesFromGrid(spritesheet, 129, 67, 10, 10, 0, 0, 1, 5, 10, 10, ballSprites);
  ballAnimator.loadSprites(ballSprites);
}

void GameScreen::loadPowerupSprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> powerupSprites;
  loadSpritesFromGrid(spritesheet, 129, 165, 44, 22, 0, 2, 7, 8, 44, 22, powerupSprites);
  powerupAnimator.loadSprites(powerupSprites);
}

void GameScreen::loadTileSprites(SDL_Surface *spritesheet) {
  std::vector<SDL_Surface *> tileSprites;
  loadSpritesFromGrid(spritesheet, 129, 1, 44, 22, 0, 0, 3, 3, 44, 22, tileSprites);
  loadSpritesFromGrid(spritesheet, 129, 77, 44, 22, 0, 0, 4, 5, 44, 22, tileSprites);
  tileAnimator.loadSprites(tileSprites);
}

SDL_Surface *GameScreen::loadSingleSprite(SDL_Surface *spritesheet, int spriteX, int spriteY, int spriteWidth, int spriteHeight) {
  return loadSingleSprite(spritesheet, spriteX, spriteY, spriteWidth, spriteHeight, spriteWidth, spriteHeight);
}

SDL_Surface *GameScreen::loadSingleSprite(SDL_Surface *spritesheet,
					 int spriteX, int spriteY,
					 int spriteWidth, int spriteHeight,
					 int resultWidth, int resultHeight) {
  std::vector<SDL_Surface *> v;
  loadSpritesFromGrid(spritesheet, spriteX, spriteY, spriteWidth, spriteHeight, 0, 0, 1, 1, resultWidth, resultHeight, v);
  return v[0];
}

void GameScreen::loadSpritesFromGrid(SDL_Surface *spritesheet, 
				     int firstSpriteX, int firstSpriteY,
				     int spriteWidth, int spriteHeight,
				     int horizontalGap, int verticalGap,
				     int rows, int columns,
				     int resultWidth, int resultHeight,
				     std::vector<SDL_Surface *> &spriteArray) {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      spriteArray.push_back(SDL_CreateRGBSurface(0, 
						 resultWidth,
						 resultHeight,
						 32, 0, 0, 0, 0));
      SDL_Rect r;
      r.x = firstSpriteX + j*(spriteWidth + horizontalGap);
      r.y = firstSpriteY + i*(spriteHeight + verticalGap);
      r.w = spriteWidth;
      r.h = spriteHeight;
      SDL_BlitScaled(spritesheet, &r, spriteArray.back(), nullptr);
      SDL_SetColorKey(spriteArray.back(), SDL_TRUE, SDL_MapRGB(spriteArray.back() -> format, 0xff, 0, 0xff));
    }
  }
}

GameScreen::GameScreen(Board &newBoard) : board(newBoard), 
					  tileAnimator(newBoard.getTiles()), 
					  powerupAnimator(newBoard.getPowerups()),
					  ballAnimator(newBoard.getBalls()),
					  enemyAnimator(newBoard.getEnemies()) {
  width = GAME_SCREEN_WIDTH;
  height = GAME_SCREEN_HEIGHT;
  board.addMonitor(&tileAnimator);
  board.addMonitor(&powerupAnimator);
  SDL_Surface *spritesheet = SDL_LoadBMP("./res/sprites/sprites.bmp");
  loadTileSprites(spritesheet);
  loadBulletSprite(spritesheet);
  loadBallSprites(spritesheet);
  loadPaddleSprites(spritesheet);
  loadPowerupSprites(spritesheet);
  loadBorderSprites(spritesheet);
  loadEnemySprites(spritesheet);
  SDL_FreeSurface(spritesheet);
}

void GameScreen::drawSpritesInRow(SDL_Surface *target, int baseX, int baseY, std::vector<SDL_Surface *> &v, bool vertical) {
  SDL_Rect r;
  r.x = baseX;
  r.y = baseY;
  for(int i = 0; i < v.size(); i++) {
    SDL_BlitSurface(v[i], nullptr, target, &r);
    if(vertical) r.y += v[i] -> h;
    else r.x += v[i] -> w;
  }
}

void GameScreen::drawBorders(SDL_Surface *target, int baseX, int baseY) {
  std::vector<SDL_Surface *> v;
  v.push_back(leftAnglePipeSprite);
  v.push_back(shortHorizontalPipeSprite);
  v.push_back(gateSprites[0]);
  v.push_back(longHorizontalPipeSprite);
  v.push_back(gateSprites[0]);
  v.push_back(shortHorizontalPipeSprite);
  v.push_back(rightAnglePipeSprite);
  drawSpritesInRow(target, baseX, baseY, v, false);
  v.clear();
  for(int i = 0; i < 5; i++) {
    v.push_back(verticalPipeSprite);
  }
  drawSpritesInRow(target, 0 + baseX, leftAnglePipeSprite -> h + baseY, v, true);
  drawSpritesInRow(target, GAME_SCREEN_WIDTH - BORDER_SIZE + baseX, rightAnglePipeSprite -> h + baseY, v, true);
}

void GameScreen::drawBullets(SDL_Surface *target, int baseX, int baseY) {
  std::vector<Bullet> &bullets = board.getBullets();
  for(int i = 0; i < bullets.size(); i++) {
    SDL_Rect r;
    r.x = bullets[i].getX() + baseX;
    r.y = bullets[i].getY() + baseY;
    SDL_BlitSurface(bulletSprite, nullptr, target, &r);
  }
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
  ballAnimator.drawShadows(target, baseX, baseY);
}

void GameScreen::drawBalls(SDL_Surface *target, int baseX, int baseY) {
  ballAnimator.drawBalls(target, baseX, baseY);
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
  SDL_BlitSurface(paddleSprites[7-player.getLength()], nullptr, target, &r);
}

void GameScreen::drawEnemies(SDL_Surface *target, int baseX, int baseY) {
  enemyAnimator.drawEnemies(target, baseX, baseY);
}

void GameScreen::drawYourself(SDL_Surface *target, int baseX, int baseY) {
  drawBackground(target, baseX, baseY);
  drawShadows(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawBullets(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawTiles(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawPowerups(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawBalls(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawBorders(target, baseX, baseY);
  drawPaddle(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  drawEnemies(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
}
