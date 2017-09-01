#include<DockedRectangle.h>
#include<MovableRectangle.h>

#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

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

 public:
  static bool collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect);
  static bool collideBorders(MovableRectangle &ball);
};

#endif
