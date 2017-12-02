#include<animators/TileAnimator.h>
#include<panes/GameScreen.h>
#include<SpriteUtils.h>

TileAnimator::TileAnimator(const std::vector<Tile> &tiles) : tiles(tiles) {

}

void TileAnimator::notifyTileDestroyed(int id) {
  framesShining.erase(id);
}

void TileAnimator::notifyTileHit(int id) {
  framesShining[id] = 0;
}

void TileAnimator::loadSprites(SDL_Surface *spritesheet) {
  SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 1, 44, 22, 0, 0, 3, 3, 44, 22, normalTiles);
  shadow = normalTiles[8];
  normalTiles.resize(8);
  SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 77, 44, 22, 0, 0, 4, 5, 44, 22, silverTiles);
  goldenTiles = std::vector<SDL_Surface *>(silverTiles.begin() + 10, silverTiles.end());
  silverTiles.resize(10);
}

void TileAnimator::drawShadows(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < tiles.size(); i++) {
    const Tile & tile = tiles[i];
    SDL_Rect r;
    r.x = tile.getX() + baseX + GameScreen::shadowOffsetX;
    r.y = tile.getY() + baseY + GameScreen::shadowOffsetY;
    SDL_BlitSurface(shadow, nullptr, target, &r);
  }
}

void TileAnimator::incrementAllFramesShining() {
  std::unordered_map<int, int> :: iterator it;
  for(it = framesShining.begin(); it != framesShining.end(); it++) {
    it -> second++;
  }
}

void TileAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  incrementAllFramesShining();
  for(int i = 0; i < tiles.size(); i++) {
    const Tile &tile = tiles[i];
    SDL_Rect r;
    r.x = tile.getX() + baseX;
    r.y = tile.getY() + baseY;
    if(tile.getColour() < 8) {
      SDL_BlitSurface(normalTiles[tile.getColour()], nullptr, target, &r);
      continue;
    }

    std::vector<SDL_Surface *> sprites = tile.getColour() == 8 ? silverTiles : goldenTiles;
    int whichSprite;
    if(framesShining.find(tile.getId()) == framesShining.end()) whichSprite = 0;
    else {
      int framesSoFar = framesShining[tile.getId()];
      whichSprite = framesShining[tile.getId()] / 3;
      if(whichSprite >= sprites.size()) {
	whichSprite = 0;
	framesShining.erase(tile.getId());
      }
    }
    SDL_BlitSurface(sprites[whichSprite], nullptr, target, &r);
  }
}

void TileAnimator::reset() {
  framesShining.clear();
}
