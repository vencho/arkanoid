#include<Board.h>
#include<Global.h>
#include<SDL.h>
#include<ctime>


int main() {
  SDL_Init(SDL_INIT_VIDEO);
  clock_t t1, t2;
  double secondsspent;
  Board B = Board(MAXX, MAXY);
  clock();
  for(int i = 0; i < 1000; i++) {
    printf("%d: ", i+1);
    t1 = clock();
    B.tick();
    B.report();
    t2 = clock();
    double secondsspent = (t2 - t1) / ( (double) CLOCKS_PER_SEC) ;

    int delay = (int)(1000*(SPF - secondsspent));
    SDL_Delay(delay);
  }

  SDL_Quit();
  return 0;
}
