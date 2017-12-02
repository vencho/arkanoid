#include<animators/BorderAnimator.h>
#include<SpriteUtils.h>
#include<panes/GameScreen.h>

BorderAnimator::BorderAnimator(const Board &board) : board(board) { }
void BorderAnimator::loadSprites(SDL_Surface *spritesheet) {
  shortHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 8, 77, 18);
  longHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 26, 218, 18);
  leftAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 5, 28, 40);
  rightAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 47, 28, 40);
  leftVerticalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 490, 96, 18, 94);
  rightVerticalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 490, 192, 18, 94);
  SpriteUtils::loadSpritesFromGrid(spritesheet, 0, 181, 90, 22, 0, 0, 7, 1, 90, 18, gateSprites);

  topPipes.push_back(leftAnglePipeSprite);
  topPipes.push_back(shortHorizontalPipeSprite);
  topPipes.push_back(gateSprites[0]);
  topPipes.push_back(longHorizontalPipeSprite);
  topPipes.push_back(gateSprites[0]);
  topPipes.push_back(shortHorizontalPipeSprite);
  topPipes.push_back(rightAnglePipeSprite);

  for(int i = 0; i*leftVerticalPipeSprite -> h + leftAnglePipeSprite -> h < GameScreen::gameScreenHeight; i++) {
    leftPipes.push_back(leftVerticalPipeSprite);
    rightPipes.push_back(rightVerticalPipeSprite);
  }
}

void BorderAnimator::drawBackground(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  r.x = baseX;
  r.y = baseY;
  r.w = GameScreen::gameScreenWidth;
  r.h = GameScreen::gameScreenHeight;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));
}

void BorderAnimator::drawBorders(SDL_Surface *target, int baseX, int baseY) {
  SpriteUtils::drawSpritesInRow(target, baseX, baseY, topPipes, false);
  SpriteUtils::drawSpritesInRow(target, 0 + baseX, leftAnglePipeSprite -> h + baseY, leftPipes, true);
  SpriteUtils::drawSpritesInRow(target, GameScreen::gameScreenWidth - GameScreen::borderSize + baseX, 
				rightAnglePipeSprite -> h + baseY, rightPipes, true);
}

void BorderAnimator::reset() { }
