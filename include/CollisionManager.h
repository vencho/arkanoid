#include<DockedRectangle.h>
#include<MovableRectangle.h>

#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

class CollisionManager {
 private:
  static void intervalSnap(MovableRectangle &ball, int tileLeft, int tileRight, bool reflect, bool x);
  static bool rectanglesIntersect(DockedRectangle &first, DockedRectangle &second);
  static bool intervalsIntersect(int a, int b, int c, int d);
  static int intervalOverlap(int a, int b, int c, int d);
  static bool intervalContainment(int a, int b, int c, int d);
  
  static DockedRectangle leftBorder;
  static DockedRectangle rightBorder;
  static DockedRectangle topBorder;
  static DockedRectangle bottomBorder;
    
 public:
  static bool collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect);
  static bool collideBorders(MovableRectangle &ball);
};

#endif
