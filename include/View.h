#include<Board.h>
#include<SDL.h>

#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED

class View {
 private:
  Board &board;
  int colours[6] = { 0, 0x00ff00, 0xffff00, 0xff0000, 0x0000ff, 0x000000 };
  
 public:
  View(Board &newBoard);
  SDL_Surface * draw();
};


#endif
