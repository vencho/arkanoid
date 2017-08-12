#include<CollisionManager.h>


CollisionManager::Line::Line(bool v, int cc, bool sss) : vertical(v), constantCoordinate(cc), smallSideSolid(sss) { }
CollisionManager::Segment::Segment(bool v, int cc, bool sss, int vcl, int vch) : 
  CollisionManager::Line::Line(v, cc, sss), variableCoordinateLow(vcl), variableCoordinateHigh(vch) { }


bool CollisionManager::collideRectangle(MovableRectangularObject &ball, RectangularObject &tile, bool reflect) {
  bool havecollided = false;
  
  havecollided |= collideSegment(ball, Segment(true, tile.getX(), false, tile.getY(), tile.getY() + tile.getHeight()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(true, tile.getX() + tile.getWidth(), true, tile.getY(), tile.getY() + tile.getHeight()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(false, tile.getY(), false, tile.getX(), tile.getX() + tile.getWidth()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(true, tile.getY(), false, tile.getX(), tile.getX() + tile.getWidth()), reflect);
  if(havecollided) return true;
  return false;
}

/*
Collision with segment. 
The first three arguments define a solid halfplane as in Ball::collideLine(x, vertical, smallsidesolid).
The arguments ylow and yhigh define the extent of the segment in the non-constant coordinate of the line.
*/
bool CollisionManager::collideSegment(
				      MovableRectangularObject &ball, 
				      Segment &S,
				      bool reflect) {
  int ballLow = S.vertical ? ball.getY() : ball.getX();
  int boundedCoordinateExtent = S.vertical ? ball.getHeight() : ball.getWidth();
  int ballHigh = ballLow + boundedCoordinateExtent;

  if(S.variableCoordinateLow > ballHigh) return false;
  if(S.variableCoordinateHigh > ballLow) return false;

  return collideLine(ball, S, reflect);
}


/*
Collision and reflection with an infinite line L.
The constant coordinate of this line is the first argument val.
This line is vertical or horizontal, indicated by the second parameter.
If smallsidesolid is true, then { z : z <= coordinate } is the solid side.
Otherwise it is { z : z >= coordinate }.
*/
bool CollisionManager::collideLine(MovableRectangularObject &ball, Line &L, bool reflect) {
  // Which coordinate of the ball matters for the reflection.
  int coordinate = L.vertical ? ball.getX() : ball.getY();

  // What is the size of the movable object in that coordinate?
  int extent = L.vertical ? ball.getWidth() : ball.getHeight();
  
  // Make coordinate refer to the centre in the relevant dimension.
  coordinate += extent / 2;

  // The velocity in that coordinate.
  int velocity = L.vertical ? ball.getVelocityX() : ball.getVelocityY();
  
  if( (velocity <= 0) != L.smallsidesolid ) return false;
  
  // One of the four tips of the ball, the one which needs to be checked
  // for membership in the solid halfplane to determine collision.
  int extremecoordinate = L.smallsidesolid ? coordinate - extent/2 : coordinate + extent/2;

  // A collision takes place if that extreme tip is in the solid halfplane.
  bool collision = L.smallsidesolid ? (extremecoordinate <= L.constantCoordinate && coordinate >= L.constantCoordinate) : 
    (extremecoordinate >= L.constantCoordinate && coordinate <= L.constantCoordinate);

  if(!collision) {
    // No reflection, no change to ball.
    return false;
  }

  // Push the ball out of the solid halfplane.
  extremecoordinate = L.constantCoordinate;
  coordinate = L.smallsidesolid ? extremecoordinate + extent/2 : extremecoordinate - extent/2;

  // Invert ball velocity in the relevant direction.
  if(reflect) velocity = -velocity;

  // Make coordinate refer to corner again.
  coordinate -= extent / 2;

  // Set the new value for coordinate, and possibly velocity.
  if(vertical) {
    ball.setX(coordinate); 
    ball.setVelocityX(velocity);
  }
  else {
    ball.setY(coordinate);
    ball.setVelocityY(velocity);
  }
  return true;
}




