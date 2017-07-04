#include<View.h>
#include<Board.h>
#include<Ball.h>

View::View(Board &newBoard) : board(newBoard) {
  
}


SDL_Surface *View::draw() {
SDL_Surface *answer = SDL_CreateRGBSurface(0, MAXX, MAXY, 32, 0, 0, 0, 0);
SDL_Rect r;

r.x = r.y = 0;
r.w = MAXX;
r.h = MAXY;
SDL_FillRect(answer, &r, SDL_MapRGB(answer->format, 255, 0, 0));

Ball &ball = board.getBall(0);
r.x = ball.getX() - BALL_R;
r.y = ball.getY() - BALL_R;
r.w = 2*BALL_R;
r.h = 2*BALL_R;
SDL_FillRect(answer, &r, SDL_MapRGB(answer->format, 0, 255, 0));

return answer;
}
