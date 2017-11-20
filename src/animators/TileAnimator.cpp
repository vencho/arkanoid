#include<animators/TileAnimator.h>

TileAnimator::TileAnimator(std::vector<Tile> &tiles) : tiles(tiles) {

}

void TileAnimator::notifyTileDestroyed(int id) {
  framesShining.erase(id);
}

void TileAnimator::notifyTileHit(int id) {
  framesShining[id] = 0;
}

void TileAnimator::loadSprites(std::vector<SDL_Surface *> &sprites) {
  normalTiles.resize(8);
  for(int i = 0; i < 8; i++) normalTiles[i] = sprites[i];
  shadow = sprites[8];

  silverTiles.resize(10);
  for(int i = 0; i < 10; i++) silverTiles[i] = sprites[i + 9];

  goldenTiles.resize(10);
  for(int i = 0; i < 10; i++) goldenTiles[i] = sprites[i + 19];
}

void TileAnimator::drawShadows(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < tiles.size(); i++) {
    Tile & tile = tiles[i];
    SDL_Rect r;
    r.x = tile.getX() + baseX + SHADOW_OFFSET_X;
    r.y = tile.getY() + baseY + SHADOW_OFFSET_Y;
    SDL_BlitSurface(shadow, nullptr, target, &r);
  }
}

void TileAnimator::incrementAllFramesShining() {
  std::unordered_map<int, int> :: iterator it;
  for(it = framesShining.begin(); it != framesShining.end(); it++) {
    it -> second++;
  }
}

void TileAnimator::drawTiles(SDL_Surface *target, int baseX, int baseY) {
  incrementAllFramesShining();
  for(int i = 0; i < tiles.size(); i++) {
    Tile &tile = tiles[i];
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
