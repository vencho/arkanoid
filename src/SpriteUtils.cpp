#include<SpriteUtils.h>

void SpriteUtils::loadSpritesFromGrid(SDL_Surface *spritesheet, 
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


SDL_Surface *SpriteUtils::loadSingleSprite(SDL_Surface *spritesheet, int spriteX, int spriteY, int spriteWidth, int spriteHeight) {
  return loadSingleSprite(spritesheet, spriteX, spriteY, spriteWidth, spriteHeight, spriteWidth, spriteHeight);
}

SDL_Surface *SpriteUtils::loadSingleSprite(SDL_Surface *spritesheet,
					     int spriteX, int spriteY,
					     int spriteWidth, int spriteHeight,
					     int resultWidth, int resultHeight) {
  std::vector<SDL_Surface *> v;
  loadSpritesFromGrid(spritesheet, spriteX, spriteY, spriteWidth, spriteHeight, 0, 0, 1, 1, resultWidth, resultHeight, v);
  return v[0];
}

void SpriteUtils::drawSpritesInRow(SDL_Surface *target, int baseX, int baseY, std::vector<SDL_Surface *> &v, bool vertical) {
  SDL_Rect r;
  r.x = baseX;
  r.y = baseY;
  for(int i = 0; i < v.size(); i++) {
    SDL_BlitSurface(v[i], nullptr, target, &r);
    if(vertical) r.y += v[i] -> h;
    else r.x += v[i] -> w;
  }
}

