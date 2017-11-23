#include<geometry/CollisionManager.h>
#include<Global.h>
#include<vector>
#include<utility>
#include<cstdio>

#define INFINITY 4000
DockedRectangle CollisionManager::leftBorder = DockedRectangle(-INFINITY, 0, INFINITY, INFINITY);
DockedRectangle CollisionManager::rightBorder = DockedRectangle(GAME_SCREEN_WIDTH, 0, INFINITY, INFINITY);
DockedRectangle CollisionManager::topBorder = DockedRectangle(0, -INFINITY, INFINITY, INFINITY);
#undef INFINITY


void CollisionManager::getIntersectionInfo(DockedRectangle &first, DockedRectangle &second, struct CollisionManager::collision_info &ans) {
  if(!rectanglesIntersect(first, second)) {
    ans.intersect[0] = false;
    ans.intersect[1] = false;
    ans.intersect[2] = false;
    ans.intersect[3] = false;
    return;
  }
  
  int x1, y1, x2, y2, x3, y3, x4, y4;
  x1 = first.getX();
  y1 = first.getY();
  x2 = first.getX() + first.getWidth() - 1;
  y2 = first.getY() + first.getHeight() - 1;

  x3 = second.getX();
  y3 = second.getY();
  x4 = second.getX() + second.getWidth() - 1;
  y4 = second.getY() + second.getHeight() - 1;

  ans.intersect[0] = (x1 <= x3 && x3 <= x2);
  ans.intersect[1] = (x1 <= x4 && x4 <= x2);
  ans.intersect[2] = (y1 <= y3 && y3 <= y2);
  ans.intersect[3] = (y1 <= y4 && y4 <= y2);

  if(ans.intersect[0]) ans.pop[0] = x2 - x3 + 1;
  if(ans.intersect[1]) ans.pop[1] = x4 - x1 + 1;
  if(ans.intersect[2]) ans.pop[2] = y2 - y3 + 1;
  if(ans.intersect[3]) ans.pop[3] = y4 - y1 + 1;
}

bool CollisionManager::collideBorders(MovableRectangle &ball) {
  bool ans = false;
  ans |= collideRectangle(ball, topBorder, 8, 2);
  ans |= collideRectangle(ball, leftBorder, 2, 1);
  ans |= collideRectangle(ball, rightBorder, 1, 1);
  return ans;
}

int CollisionManager::collideRectangle(MovableRectangle &first, 
				       DockedRectangle &second, 
				       int allowedPopDirections, 
				       int allowedReflects) {
  if(first.isMovingX(true)) allowedPopDirections &= 14;
  if(first.isMovingX(false)) allowedPopDirections &= 13;
  if(first.isMovingY(true)) allowedPopDirections &= 11;
  if(first.isMovingY(false)) allowedPopDirections &= 7;
  
  struct CollisionManager::collision_info info;
  getIntersectionInfo(first, second, info);

  int directionsPopped = popRectangle(first, second, allowedPopDirections, info);
  if( (directionsPopped & 1) || (directionsPopped & 2) ) {
    if( allowedReflects & 1 ) {
      first.reflectOrthogonally(true);
    }
  }

  if( (directionsPopped & 4) || (directionsPopped & 8) ) {
    if( allowedReflects & 2 ) {
      first.reflectOrthogonally(false);
    }
  }

  return directionsPopped;
}

/* 
Assuming rectangles first and second intersect, 
push first out of second in the direction of the
closest side of second which is intersected by first. 

Sides of second can be excluded from consideration
by setting their corresponding bits in allowedPopDirections
to zero. Bits 0 to 3 correspond to left, right, top, bottom
in that order.

If two edges are equally near and both allowed, then push
out in both directions.
*/
int CollisionManager::popRectangle(DockedRectangle &first, 
				   DockedRectangle &second, 
				   int allowedPopDirections, 
				   CollisionManager::collision_info &info) {

  int best_direction = -1;
  for(int i = 0; i < 4; i++) {
    if(info.intersect[i] && (allowedPopDirections & (1 << i))) {
      if(best_direction == -1 || info.pop[i] < info.pop[best_direction]) {
	best_direction = i;
      }
    }
  }

  int other_best_direction = -1;
  for(int i = 0; i < 4; i++) {
    if(i != best_direction && (allowedPopDirections & (1 << i)) && info.intersect[i] && info.pop[i] == info.pop[best_direction]) {
      other_best_direction = i;
      break;
    }
  }

  int directionsPopped = 0;
  if(best_direction != -1) directionsPopped += (1 << best_direction);
  if(other_best_direction != -1) directionsPopped += (1 << other_best_direction);

  if(directionsPopped & 1) first.setX(first.getX() - info.pop[0]);
  else if(directionsPopped & 2) first.setX(first.getX() + info.pop[1]);
  else if(directionsPopped & 4) first.setY(first.getY() - info.pop[2]);
  else if(directionsPopped & 8) first.setY(first.getY() + info.pop[3]);

  return directionsPopped;
}



/* Do the closed intervals [a,b] and [c,d] intersect? */
bool CollisionManager::intervalsIntersect(int a, int b, int c, int d) {
  return intervalOverlap(a, b, c, d) > 0;
}

/* Is the closed interval [a, b] contained in the closed interval [c,d]? */
bool CollisionManager::intervalContainment(int a, int b, int c, int d) {
  return c <= a && b <= d;
}

/* What is the length of the intersection of the closed intervals [a,b] and [c,d]? */
int CollisionManager::intervalOverlap(int a, int b, int c, int d) {
  if(b < c || d < a) return 0;
  if(intervalContainment(a, b, c, d)) return d-c+1;
  if(intervalContainment(c, d, a, b)) return b-a+1;
  if(a <= c) return b-c+1;
  return d-a+1;
}

/* Do the rectangles first and second intersect? */
bool CollisionManager::rectanglesIntersect(DockedRectangle &first, DockedRectangle &second) {
  bool a = intervalsIntersect(first.getX(), first.getX() + first.getWidth()-1, 
			      second.getX(), second.getX() + second.getWidth()-1);
  bool b = intervalsIntersect(first.getY(), first.getY() + first.getHeight()-1, 
			      second.getY(), second.getY() + second.getHeight()-1);
  return a && b;
}
