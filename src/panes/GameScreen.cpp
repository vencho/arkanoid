#include<panes/GameScreen.h>
#include<model/Board.h>
#include<SDL.h>

GameScreen::GameScreen(Board &board) : board(board), 
				       tileAnimator(board.getTiles()), 
				       powerupAnimator(board.getPowerups()),
				       ballAnimator(board.getBalls()),
				       enemyAnimator(board.getEnemies()),
				       paddleAnimator(board),
				       borderAnimator(board),
				       bulletAnimator(board),
				       explosionAnimator() {
  width = GAME_SCREEN_WIDTH;
  height = GAME_SCREEN_HEIGHT;

  board.addMonitor(&tileAnimator);
  board.addMonitor(&powerupAnimator);
  board.addMonitor(&explosionAnimator);

  SDL_Surface *spritesheet = SDL_LoadBMP("./res/sprites/sprites.bmp");
  tileAnimator.loadSprites(spritesheet);
  ballAnimator.loadSprites(spritesheet);
  paddleAnimator.loadSprites(spritesheet);
  powerupAnimator.loadSprites(spritesheet);
  borderAnimator.loadSprites(spritesheet);
  bulletAnimator.loadSprites(spritesheet);
  enemyAnimator.loadSprites(spritesheet);
  explosionAnimator.loadSprites(spritesheet);
  SDL_FreeSurface(spritesheet);
}

void GameScreen::drawYourself(SDL_Surface *target, int baseX, int baseY) {
  borderAnimator.drawBackground(target, baseX, baseY);
  tileAnimator.drawShadows(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  ballAnimator.drawShadows(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  bulletAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  tileAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  powerupAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  ballAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  borderAnimator.drawBorders(target, baseX, baseY);
  paddleAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  enemyAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
  explosionAnimator.draw(target, baseX + BORDER_SIZE, baseY + BORDER_SIZE);
}
