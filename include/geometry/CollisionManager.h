#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include<geometry/DockedRectangle.h>
#include<geometry/MovableRectangle.h>
#include<utility>

class CollisionManager {
 private:
  struct collision_info {
    // left, right, top, bottom
    bool intersect[4];
    int pop[4];
  };

  static bool intervalsIntersect(int a, int b, int c, int d);
  static int intervalOverlap(int a, int b, int c, int d);
  static bool intervalContainment(int a, int b, int c, int d);
  static int popRectangle(DockedRectangle &first, DockedRectangle &second, int allowedPopDirections, struct collision_info &info);
  
  static DockedRectangle leftBorder;
  static DockedRectangle rightBorder;
  static DockedRectangle topBorder;
  static DockedRectangle bottomBorder;
  static void getIntersectionInfo(DockedRectangle &first, DockedRectangle &second, struct collision_info &ans);


 public:
  static bool rectanglesIntersect(DockedRectangle &first, DockedRectangle &second);
  static bool collideBorders(MovableRectangle &ball);

  // allowedPopDirections is a four-bit mask (left, right, top, bottom)
  // allowedReflects is a two-bit mask (x, y)
  static int collideRectangle(MovableRectangle &first, DockedRectangle &second, int allowedPopDirections, int allowedReflects) ;
};

#endif
