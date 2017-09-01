#include<CollisionManager.h>
#include<Global.h>

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
Collision with tile.
*/
bool CollisionManager::collideRectangle(MovableRectangle &ball, DockedRectangle &tile, bool reflect) {
  bool havecollided = false;
  
  havecollided |= collideSegment(ball, Segment(true, tile.getX(), false, tile.getY(), tile.getY() + tile.getHeight()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(true, tile.getX() + tile.getWidth(), true, tile.getY(), tile.getY() + tile.getHeight()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(false, tile.getY(), false, tile.getX(), tile.getX() + tile.getWidth()), reflect);
  if(havecollided) return true;
  havecollided |= collideSegment(ball, Segment(false, tile.getY() + tile.getHeight(), true, tile.getX(), tile.getX() + tile.getWidth()), reflect);
  if(havecollided) return true;
  return false;
}

/*
Collision with segment. 
*/
bool CollisionManager::collideSegment(
				      MovableRectangle &ball, 
				      CollisionManager::Segment S,
				      bool reflect) {
  int ballLow = S.vertical ? ball.getY() : ball.getX();
  int boundedCoordinateExtent = S.vertical ? ball.getHeight() : ball.getWidth();
  int ballHigh = ballLow + boundedCoordinateExtent;

  if(S.variableCoordinateLow > ballHigh) return false;
  if(S.variableCoordinateHigh < ballLow) return false;

  return collideLine(ball, S, reflect);
}

bool CollisionManager::collideBorders(MovableRectangle &ball) {
  bool havecollided;
  havecollided |= collideLine(ball, Line(true, 0, true), true);
  havecollided |= collideLine(ball, Line(false, 0, true), true);
  havecollided |= collideLine(ball, Line(true, MAXX, false), true);
  //  havecollided |= collideLine(ball, Line(false, MAXY, false), true);
  return havecollided;
}

/*
Collision and reflection with an infinite line L.
*/
bool CollisionManager::collideLine(MovableRectangle &ball, 
					  CollisionManager::Line L, 
					  bool reflect) {
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

  // Set the new value for coordinate and velocity.
  if(L.vertical) {
    ball.setX(coordinate); 
    ball.setVelocityX(velocity);
  }
  else {
    ball.setY(coordinate);
    ball.setVelocityY(velocity);
  }
  return true;
}




