#include<RectangularObject.h>
#include<MovableRectangularObject.h>

#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

class CollisionManager {
 public:
  void collide(MovableRectangularObject &, RectangularObject &);
  void collide(MovableRectangularObject &, MovableRectangularObject &, bool, bool);

 private:
  class Line {
  public:
    bool vertical;
    int constantCoordinate;
    bool smallSideSolid;
    Line(bool v, int cc, bool sss);
  };

  class Segment : public Line {
  public:
    int variableCoordinateLow;
    int variableCoordinateHigh;
    Segment(bool v, int cc, bool sss, int vcl, int vch);
  };
};

#endif
