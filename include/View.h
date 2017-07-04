#include<Board.h>
#include<SDL.h>

#ifndef VIEW_H_DEFINED
#define VIEW_H_DEFINED

class View {
 private:
  Board &board;
  
 public:
  View(Board &newBoard);
  SDL_Surface * draw();
};


#endif
