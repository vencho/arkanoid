#include<CollisionManager.h>
#include<Global.h>
#include<cstdio>

#define INFINITY 4000
DockedRectangle CollisionManager::leftBorder = DockedRectangle(-INFINITY, 0, INFINITY, INFINITY);
DockedRectangle CollisionManager::rightBorder = DockedRectangle(GAME_SCREEN_WIDTH, 0, INFINITY, INFINITY);
DockedRectangle CollisionManager::topBorder = DockedRectangle(0, -INFINITY, INFINITY, INFINITY);
// DockedRectangle CollisionManager::bottomBorder = DockedRectangle(0, GAME_SCREEN_HEIGHT, INFINITY, INFINITY);
#undef INFINITY

bool CollisionManager::collideBorders(MovableRectangle &ball) {
  bool ans = false;
  ans |= collideRectangle(ball, topBorder, true);
  ans |= collideRectangle(ball, leftBorder, true);
  ans |= collideRectangle(ball, rightBorder, true);
  //  ans |= collideRectangle(ball, bottomBorder, true);
  return ans;
}

bool CollisionManager::rectanglesIntersect(DockedRectangle &first, DockedRectangle &second) {
  bool a = intervalsIntersect(first.getX(), first.getX() + first.getWidth()-1, 
			      second.getX(), second.getX() + second.getWidth()-1);
  bool b = intervalsIntersect(first.getY(), first.getY() + first.getHeight()-1, 
			      second.getY(), second.getY() + second.getHeight()-1);
  return a && b;
}

int CollisionManager::intervalOverlap(int a, int b, int c, int d) {
  if(b < c || d < a) return 0;
  if(intervalContainment(a, b, c, d)) return d-c+1;
  if(intervalContainment(c, d, a, b)) return b-a+1;
  if(a <= c) return b-c+1;
  return d-a+1;
}

bool CollisionManager::intervalContainment(int a, int b, int c, int d) {
  return c <= a && b <= d;
}

bool CollisionManager::intervalsIntersect(int a, int b, int c, int d) {
  return intervalOverlap(a, b, c, d) > 0;
}

bool CollisionManager::collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect) {
  int a, b, c, d;
  a = ball.getX(); 
  b = ball.getX() + ball.getWidth()-1;
  c = tile.getX(); 
  d = tile.getX() + tile.getWidth()-1;
  int u = intervalOverlap(a,b,c,d);

  int x, y, z, w;
  x = ball.getY();
  y = ball.getY() + ball.getHeight()-1;
  z = tile.getY();
  w = tile.getY() + tile.getHeight()-1;
  int v = intervalOverlap(x, y, z, w);

  if(!u || !v) return false;
#define snapX { intervalSnap(ball, tile.getX(), tile.getX() + tile.getWidth() - 1, reflect, true); return true; }
#define snapY { intervalSnap(ball, tile.getY(), tile.getY() + tile.getHeight() - 1, reflect, false); return true; }

  if(intervalContainment(a, b, c, d) || intervalContainment(c, d, a, b)) snapY ;
  if(intervalContainment(x, y, z, w) || intervalContainment(z, w, x, y)) snapX ;
  
  if(v >= u) snapY;
  snapX;
  return true;
}

void CollisionManager::intervalSnap(MovableRectangle &ball, int tileLeft, int tileRight, bool reflect, bool x) {
  int & ballLeft = x ? ball.getX() : ball.getY();
  int & ballv = x ? ball.getVelocityX() : ball.getVelocityY();
  int ballExtent = x ? ball.getWidth() : ball.getHeight();
  int ballRight = ballLeft + ballExtent - 1;

#define popleft { ballRight = tileLeft - 1;\
    ballLeft = ballRight - (ballExtent-1);\
    if(reflect) { printf("reflecting\n"); ballv = -ballv; }	\
    printf("popleft\n"); \
  }
#define popright {  ballLeft = tileRight + 1; \
  ballRight = ballLeft + (ballExtent-1); \
  if(reflect) { printf("reflecting\n"); ballv = -ballv; } \
  printf("popright\n"); \
  }


  if( (tileLeft <= ballLeft && ballRight <= tileRight) || (ballLeft <= tileLeft && tileRight <= ballRight) )
    return;

  if(tileLeft <= ballLeft) popright
  else popleft 

#undef popleft
#undef popright
}



