#include<animators/BorderAnimator.h>
#include<SpriteUtils.h>
#include<panes/GameScreen.h>

BorderAnimator::BorderAnimator(const Board &board) : board(board) { }
void BorderAnimator::loadSprites(SDL_Surface *spritesheet, SDL_Surface *backgrounds) {
  shortHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 8, 77, 18);
  longHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 26, 218, 18, Board::playAreaWidth - 177*2, 18);
  leftAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 5, 28, 40);
  rightAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 47, 28, 40);
  leftVerticalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 490, 96, 18, 94);
  rightVerticalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 490, 192, 18, 94);
  SpriteUtils::loadSpritesFromGrid(spritesheet, 0, 181, 90, 22, 0, 0, 7, 1, 90, 18, gateSprites);
  shimmerSprite = SpriteUtils::loadSingleSprite(spritesheet, 3, 792, 18, 86);

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
  rightPipesWithShimmer = rightPipes;
  rightPipesWithShimmer.pop_back();
  rightPipesWithShimmer.pop_back();
  rightPipesWithShimmer.push_back(shimmerSprite);
  rightPipesWithShimmer.push_back(shimmerSprite);

  SpriteUtils::loadSpritesFromGrid(backgrounds, 0, 0, 32, 32, 0, 0, 10, 28, 32, 32, bgSprites);
  curBgSpriteIdx = rand() % bgSprites.size();
}

void BorderAnimator::drawBackground(SDL_Surface *target, int baseX, int baseY) {
  int x, y;
  for(int x = 0; x < Board::playAreaWidth; x += bgSprites[curBgSpriteIdx] -> w) {
    for(int y = 0; y < Board::playAreaHeight; y += bgSprites[curBgSpriteIdx] -> h) {
      SDL_Rect r;
      r.x = x + baseX;
      r.y = y + baseY;
      SDL_BlitSurface(bgSprites[curBgSpriteIdx], nullptr, target, &r);
    }
  }
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
  std::vector<SDL_Surface *> &rp = board.isPortalOpen() ? rightPipesWithShimmer : rightPipes;
  SpriteUtils::drawSpritesInRow(target, GameScreen::gameScreenWidth - GameScreen::borderSize + baseX, 
				rightAnglePipeSprite -> h + baseY, rp, true);
}

void BorderAnimator::reset() { 
  curBgSpriteIdx = rand() % bgSprites.size();
}
