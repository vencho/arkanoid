#include<drawers/TileDrawer.h>
#include<SDL.h>

TileDrawer::TileDrawer() {
  SDL_Surface *spritesheet = SDL_LoadBMP("./res/sprites/sprites.bmp");
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 4; j++) {
      int idx = 4*i + j;
      tileSprites[idx] = SDL_CreateRGBSurface(0, 
					      TILE_WIDTH + shadowExtentRight, 
					      TILE_HEIGHT + shadowExtentDown, 
					      32, 0, 0, 0, 0);

      SDL_Rect r;
      r.x = 129 + j*(TILE_WIDTH + shadowExtentRight + 2);
      r.y = 1 + i*(TILE_HEIGHT + shadowExtentDown + 2);
      r.w = TILE_WIDTH + shadowExtentRight;
      r.h = TILE_HEIGHT + shadowExtentDown;
      SDL_BlitSurface(spritesheet, &r, tileSprites[idx], nullptr);
      SDL_SetColorKey(tileSprites[idx], SDL_TRUE, SDL_MapRGB(tileSprites[idx] -> format, 0xff, 0, 0xff));
    }
  }
  SDL_FreeSurface(spritesheet);
}

void TileDrawer::draw(SDL_Surface *target, int baseX, int baseY, Tile &tile) {
  SDL_Rect r;
  r.x = tile.getX() + baseX;
  r.y = tile.getY() + baseY;
  r.w = TILE_WIDTH + shadowExtentRight;
  r.h = TILE_HEIGHT + shadowExtentDown;
  SDL_BlitSurface(tileSprites[tile.getHealth()], nullptr, target, &r);
}
