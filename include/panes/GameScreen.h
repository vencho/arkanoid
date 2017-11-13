#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED
#include<SDL.h>
#include<panes/DrawablePane.h>
#include<model/Board.h>
#include<animators/TileAnimator.h>

class GameScreen : public DrawablePane {
 private:
  Board &board;
  void drawBackground(SDL_Surface *target, int baseX, int baseY);
  void drawBall(SDL_Surface *target, int baseX, int baseY);
  void drawTiles(SDL_Surface *target, int baseX, int baseY);
  void drawPaddle(SDL_Surface *target, int baseX, int baseY);
  void drawShadows(SDL_Surface *target, int baseX, int baseY);
  TileAnimator tileAnimator;
  std::vector<SDL_Surface *> ballSprites;
  std::vector<SDL_Surface *> paddleSprites;
  void loadBallSprites(SDL_Surface *spritesheet);
  void loadTileSprites(SDL_Surface *spritesheet);
  void loadPaddleSprites(SDL_Surface *spritesheet);
  void loadSpritesFromGrid(SDL_Surface *spritesheet, int firstSpriteX, int firstSpriteY,
			   int spriteWidth, int spriteHeight,
			   int horizontalGap, int verticalGap,
			   int rows, int columns,
			   std::vector<SDL_Surface *> &spriteArray);


 public:
  GameScreen(Board &newBoard);

 protected:
  virtual void drawYourself(SDL_Surface *target, int baseX, int baseY);
};


#endif
