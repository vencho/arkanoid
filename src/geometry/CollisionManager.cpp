#include<geometry/CollisionManager.h>
#include<Global.h>
#include<vector>
#include<utility>
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


CollisionManager::Line::Line(bool vertical, int constantCoordinate, bool smallsidesolid) 
  : vertical(vertical), constantCoordinate(constantCoordinate), smallsidesolid(smallsidesolid) { }
CollisionManager::Segment::Segment(bool vertical, 
				   int constantCoordinate, 
				   bool smallsidesolid, 
				   int variableCoordinateLow, 
				   int variableCoordinateHigh) : 
  CollisionManager::Line::Line(vertical, constantCoordinate, smallsidesolid), 
  variableCoordinateLow(variableCoordinateLow), 
  variableCoordinateHigh(variableCoordinateHigh) { }


/*
  Does the line from (x1, y1) in the direction (x2, y2) intersect the segment s?
  If it does, what is the t such that (x1, y1) + t(x2-x1, y2-y1) lies on the segment?
  If there are many, use the one with smallest absolute value.
*/
std::pair<bool, double> CollisionManager::timeToIntersection(int x1, int y1, int x2, int y2, Segment &s) {
  int a = s.vertical ? x2 - x1 : y2 - y1;
  int b = (s.vertical ? x1 : y1) - s.constantCoordinate;

  // Movement is parallel to line of segment s.
  if(a == 0) { 

    // Movement is along a separate line, no intersection.
    if(b != 0) return std::make_pair(false, 0);

    // Look at the non-constant coordinate.
    int var = s.vertical ? y1 : x1;
    // And at the speed in that coordinate.
    int c = s.vertical ? y2 - y1 : x2 - x1;

    // Segment lies ahead, return a positive time.
    if(var < s.variableCoordinateLow) return std::make_pair(true, (s.variableCoordinateLow - var) / (double) c);
    // Segment lies behind, return a negative time.
    if(var > s.variableCoordinateHigh) return std::make_pair(true, (s.variableCoordinateHigh - var) / (double) c);
    // We are on segment, return zero.
    return std::make_pair(true, 0);
  }

  // This many time units until defining line of s is intersected. Now or never.
  double t = -b / (double) a;
  // Calculate other coordinate at intersection.
  double var = s.vertical ? y1 + t*(y2-y1) : x1 + t*(x2-x1);
  // Does it lie inside segment.
  return std::make_pair( (double) s.variableCoordinateLow <= var && var <= (double) s.variableCoordinateHigh, t);
}


/* 
   Moving from its position at the last instant, does the ball ever 
   intersect the segment and at what time?

   Assumes no intersection at last instant.
*/
std::pair<bool, double> CollisionManager::timeToIntersectionSinceLastTick(MovableRectangle &ball, Segment &s) {
  if(ball.getVelocityX() == 0 && ball.getVelocityY() == 0) return std::make_pair(false, 0);

  double bestT;
  bool init = false;
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      int x1 = ball.getX() + i*(ball.getWidth()-1) - ball.getVelocityX();
      int y1 = ball.getY() + j*(ball.getHeight()-1) - ball.getVelocityY();
      int x2 = ball.getX() + i*(ball.getWidth()-1);
      int y2 = ball.getY() + j*(ball.getHeight()-1);
      std::pair<bool, double> ans = timeToIntersection(x1, y1, x2, y2, s);
      if(!ans.first || ans.second < 0) continue;
      if(!init || bestT > ans.second) {
	bestT = ans.second;
	init = true;
      }
    }
  }

  if(!init) return std::make_pair(false, 0);
  return std::make_pair(true, bestT);
}


bool CollisionManager::intervalsIntersect(int a, int b, int c, int d) {
  return intervalOverlap(a, b, c, d) > 0;
}
bool CollisionManager::intervalContainment(int a, int b, int c, int d) {
  return c <= a && b <= d;
}
int CollisionManager::intervalOverlap(int a, int b, int c, int d) {
  if(b < c || d < a) return 0;
  if(intervalContainment(a, b, c, d)) return d-c+1;
  if(intervalContainment(c, d, a, b)) return b-a+1;
  if(a <= c) return b-c+1;
  return d-a+1;
}




bool CollisionManager::rectanglesIntersect(DockedRectangle &first, DockedRectangle &second) {
  bool a = intervalsIntersect(first.getX(), first.getX() + first.getWidth()-1, 
			      second.getX(), second.getX() + second.getWidth()-1);
  bool b = intervalsIntersect(first.getY(), first.getY() + first.getHeight()-1, 
			      second.getY(), second.getY() + second.getHeight()-1);
  return a && b;
}


/*
Does a moving rectangle intersect a docked rectangle?
If it does, then push it out and possibly reflect velocity.
*/
bool CollisionManager::collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect) {
  if(!rectanglesIntersect(ball, tile)) return false;

  std::vector<Segment> s; // top, bottom, left, right;
  s.push_back(Segment(false, tile.getY(), false, tile.getX(), tile.getX() + tile.getWidth() - 1));
  s.push_back(Segment(false, tile.getY()+tile.getHeight()-1, true, tile.getX(), tile.getX() + tile.getWidth() - 1));
  s.push_back(Segment(true, tile.getX(), false, tile.getY(), tile.getY() + tile.getHeight() - 1));
  s.push_back(Segment(true, tile.getX()+tile.getWidth()-1, true, tile.getY(), tile.getY() + tile.getHeight() - 1));

  std::pair<bool, double> ar[4];
  for(int i = 0; i < 4; i++) ar[i] = timeToIntersectionSinceLastTick(ball, s[i]);

  int j = -1;
  for(int i = 0; i < 4; i++) {
    if(ar[i].first) {
      if(j == -1 || ar[i].second < ar[j].second) {
	j = i;
      }
    }
  }
  if(j == -1) { return false; }

  int k = -1;
  for(int i = 0; i < 4; i++) {
    if(ar[i].first && i != j) {
      if( (ar[i].second - ar[j].second) < 0.000001 ) {
	k = i;
	break;
      }
    }
  }

  if(k == -1) {
    snapToLine(ball, Line(s[j].vertical, s[j].constantCoordinate, s[j].smallsidesolid), true);
  }
  else {
    bool flag1 = headingInside(ball, s[j]);
    bool flag2 = headingInside(ball, s[k]);
    if(flag1) snapToLine(ball, Line(s[j].vertical, s[j].constantCoordinate, s[j].smallsidesolid), true);
    else snapToLine(ball, Line(s[k].vertical, s[k].constantCoordinate, s[k].smallsidesolid), true);
  }
  return true;
}

bool CollisionManager::headingInside(MovableRectangle &ball, CollisionManager::Segment s) {
  int velocity = s.vertical ? ball.getVelocityX() : ball.getVelocityY();
  return (velocity < 0 && s.smallsidesolid) || (velocity > 0 && !s.smallsidesolid);
}


/*
Snaps a moving rectangle to a line, possibly reflecting the velocity.

Typically called when the ball has intersected a tile and we wish to
push it out and reflect.
*/
void CollisionManager::snapToLine(MovableRectangle &ball, 
				   CollisionManager::Line L, 
				   bool reflect) {
  int coordinate = L.vertical ? ball.getX() : ball.getY();
  int velocity = L.vertical ? ball.getVelocityX() : ball.getVelocityY();
  int extent = L.vertical ? ball.getWidth() : ball.getHeight();

  if(L.smallsidesolid) coordinate = L.constantCoordinate+1;
  else coordinate = L.constantCoordinate - extent;

  if(reflect) velocity = -velocity;

  if(L.vertical) {
    ball.setX(coordinate);
    ball.setVelocityX(velocity);
  }
  else {
    ball.setY(coordinate);
    ball.setVelocityY(velocity);
  }
}

