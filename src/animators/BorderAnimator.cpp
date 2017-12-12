#include<animators/BorderAnimator.h>
#include<SpriteUtils.h>
#include<panes/GameScreen.h>

BorderAnimator::BorderAnimator(const Board &board) : board(board) { }
void BorderAnimator::loadSprites(SDL_Surface *spritesheet) {
  shortHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 8, 77, 18);
  longHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 26, 218, 18, Board::playAreaWidth - 177*2, 18);
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

int BorderAnimator::chooseGateSprite(int x) {
  switch(x / 5) {
  case 0:
  case 10:
    return 1;
  case 1:
  case 9:
    return 2;
  case 2:
  case 8:
    return 3;
  case 3:
  case 7:
    return 4;
  case 4:
  case 6:
    return 5;
  case 5:
    return 6;
  default:
    return 0;
  };
  return 0;
}

void BorderAnimator::selectGateSprites() {
  topPipes[2] = gateSprites[chooseGateSprite(board.getTicksSinceSpawnLeft())];
  topPipes[4] = gateSprites[chooseGateSprite(board.getTicksSinceSpawnRight())];
}

void BorderAnimator::drawBorders(SDL_Surface *target, int baseX, int baseY) {
  selectGateSprites();
  SpriteUtils::drawSpritesInRow(target, baseX, baseY, topPipes, false);
  SpriteUtils::drawSpritesInRow(target, 0 + baseX, leftAnglePipeSprite -> h + baseY, leftPipes, true);
  SpriteUtils::drawSpritesInRow(target, GameScreen::gameScreenWidth - GameScreen::borderSize + baseX, 
				rightAnglePipeSprite -> h + baseY, rightPipes, true);
}

void BorderAnimator::reset() { }
