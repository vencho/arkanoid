#include<panes/GameScreen.h>
#include<model/Board.h>
#include<SDL.h>

GameScreen::GameScreen(Board &board) : tileAnimator(board.getTiles()), 
				       powerupAnimator(board.getPowerups()),
				       ballAnimator(board.getBalls()),
				       enemyAnimator(board.getEnemies()),
				       paddleAnimator(board),
				       borderAnimator(board),
				       bulletAnimator(board),
				       explosionAnimator() {
  width = gameScreenWidth;
  height = gameScreenHeight;
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
  tileAnimator.drawShadows(target, baseX + borderSize, baseY + borderSize);
  ballAnimator.drawShadows(target, baseX + borderSize, baseY + borderSize);
  bulletAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  tileAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  powerupAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  ballAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  borderAnimator.drawBorders(target, baseX, baseY);
  paddleAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  enemyAnimator.draw(target, baseX + borderSize, baseY + borderSize);
  explosionAnimator.draw(target, baseX + borderSize, baseY + borderSize);
}

void GameScreen::reset() {
  borderAnimator.reset();
  tileAnimator.reset();
  ballAnimator.reset();
  bulletAnimator.reset();
  powerupAnimator.reset();
  paddleAnimator.reset();
  enemyAnimator.reset();
  explosionAnimator.reset();
}
