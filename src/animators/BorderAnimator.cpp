#include<animators/BorderAnimator.h>
#include<SpriteUtils.h>

BorderAnimator::BorderAnimator(Board &board) : board(board) { }
void BorderAnimator::loadSprites(SDL_Surface *spritesheet) {
  loadBorderSprites(spritesheet);
}

void BorderAnimator::loadBorderSprites(SDL_Surface *spritesheet) {
  shortHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 8, 77, 18);
  longHorizontalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 261, 26, 218, 18);
  leftAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 5, 28, 40);
  rightAnglePipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 479, 47, 28, 40);
  verticalPipeSprite = SpriteUtils::loadSingleSprite(spritesheet, 490, 96, 18, 94);
  SpriteUtils::loadSpritesFromGrid(spritesheet, 0, 181, 90, 22, 0, 0, 7, 1, 90, 18, gateSprites);
}

void BorderAnimator::drawBackground(SDL_Surface *target, int baseX, int baseY) {
  SDL_Rect r;
  r.x = baseX;
  r.y = baseY;
  r.w = GAME_SCREEN_WIDTH;
  r.h = GAME_SCREEN_HEIGHT;
  SDL_FillRect(target, &r, SDL_MapRGB(target->format, 0xcd, 0xcd, 0xcd));
}

void BorderAnimator::drawBorders(SDL_Surface *target, int baseX, int baseY) {
  std::vector<SDL_Surface *> v;
  v.push_back(leftAnglePipeSprite);
  v.push_back(shortHorizontalPipeSprite);
  v.push_back(gateSprites[0]);
  v.push_back(longHorizontalPipeSprite);
  v.push_back(gateSprites[0]);
  v.push_back(shortHorizontalPipeSprite);
  v.push_back(rightAnglePipeSprite);
  SpriteUtils::drawSpritesInRow(target, baseX, baseY, v, false);
  v.clear();
  for(int i = 0; i < 5; i++) {
    v.push_back(verticalPipeSprite);
  }
  SpriteUtils::drawSpritesInRow(target, 0 + baseX, leftAnglePipeSprite -> h + baseY, v, true);
  SpriteUtils::drawSpritesInRow(target, GAME_SCREEN_WIDTH - BORDER_SIZE + baseX, rightAnglePipeSprite -> h + baseY, v, true);
}
