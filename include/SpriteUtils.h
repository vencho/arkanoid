#ifndef SPRITE_UTILS_H_DEFINED
#define SPRITE_UTILS_H_DEFINED

#include<SDL.h>
#include<vector>

class SpriteUtils {
 public:
  static void loadSpritesFromGrid(SDL_Surface *spritesheet, 
				  int firstSpriteX, int firstSpriteY,
				  int spriteWidth, int spriteHeight,
				  int horizontalGap, int verticalGap,
				  int rows, int columns,
				  int resultWidth, int resultHeight,
				  std::vector<SDL_Surface *> &spriteArray);

  static SDL_Surface *loadSingleSprite(SDL_Surface *spritesheet, 
				       int spriteX, int spriteY, 
				       int spriteWidth, int spriteHeight);

  static SDL_Surface *loadSingleSprite(SDL_Surface *spritesheet,
				       int spriteX, int spriteY,
				       int spriteWidth, int spriteHeight,
				       int resultWidth, int resultHeight);

  static void drawSpritesInRow(SDL_Surface *target, 
			       int baseX, int baseY, 
			       std::vector<SDL_Surface *> &v, 
			       bool vertical);
};
#endif
