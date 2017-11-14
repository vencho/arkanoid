#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include<geometry/DockedRectangle.h>
#include<geometry/MovableRectangle.h>
#include<utility>

class CollisionManager {

 private:
  class Line {
  public:
    bool vertical;
    int constantCoordinate;
    bool smallsidesolid;
    Line(bool v, int cc, bool sss);
  };

  class Segment : public Line {
  public:
    int variableCoordinateLow;
    int variableCoordinateHigh;
    Segment(bool v, int cc, bool sss, int vcl, int vch);
  };

  static bool collideLine(MovableRectangle &ball, Line L, bool reflect);
  static bool collideSegment(MovableRectangle &ball, Segment S, bool reflect);
  static void snapToLine(MovableRectangle &ball, Line L, bool reflect);
  static std::pair<bool, double> timeToIntersection(int x1, int y1, int x2, int y2, Segment &s);
  static std::pair<bool, double> timeToIntersectionSinceLastTick(MovableRectangle &ball, Segment &s);
  static bool intervalsIntersect(int a, int b, int c, int d);
  static int intervalOverlap(int a, int b, int c, int d);
  static bool intervalContainment(int a, int b, int c, int d);
  static bool headingInside(MovableRectangle &ball, CollisionManager::Segment s);
  

  static DockedRectangle leftBorder;
  static DockedRectangle rightBorder;
  static DockedRectangle topBorder;
  static DockedRectangle bottomBorder;


 public:
  static bool rectanglesIntersect(DockedRectangle &first, DockedRectangle &second);
  static bool collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect);
  static bool collideBorders(MovableRectangle &ball);

};

#endif
