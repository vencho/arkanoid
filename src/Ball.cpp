#include<Ball.h>
#include<cstdio>

Ball::Ball(int x, int y, int dx, int dy) {
  this -> x = x;
  this -> y = y;
  this -> dx = dx;
  this -> dy = dy;
}

int Ball::getX() {
  return x;
}

int Ball::getY() {
  return y;
}

void Ball::tick() {
  move();
}

void Ball::move() {
  x += dx; y += dy;
}

void Ball::collide(Paddle &player) {

}

/*
Collision and reflection with an infinite line L.
The constant coordinate of this line is the first argument val.
This line is vertical or horizontal, indicated by the second parameter.
If smallsidesolid is true, then { z : z <= coordinate } is the solid side.
Otherwise it is { z : z >= coordinate }.
*/
bool Ball::collideLine(int val, bool vertical, bool smallsidesolid) {
  // Which coordinate of the ball matters for the reflection.
  int &coordinate = vertical ? x : y;
  // The velocity in that coordinate.
  int &velocity = vertical ? dx : dy;
  
  if( (velocity <= 0) != smallsidesolid ) return false;
  
  // One of the four tips of the ball, the one which needs to be checked
  // for membership in the solid halfplane to determine collision.
  int extremecoordinate = smallsidesolid ? coordinate - BALL_R : coordinate + BALL_R;
  // A collision takes place if that extreme tip is in the solid halfplane.
  bool collision = smallsidesolid ? (extremecoordinate <= val && coordinate >= val) : 
    (extremecoordinate >= val && coordinate <= val);

  if(!collision) {
    // No reflection, no change to ball.
    return false;
  }

  // Push the ball out of the solid halfplane.
  extremecoordinate = val;
  coordinate = smallsidesolid ? extremecoordinate + BALL_R : extremecoordinate - BALL_R;

  // Invert ball velocity in the relevant direction.
  velocity = -velocity;
  return true;
}

/*
Collision with segment. 
The first three arguments define a solid halfplane as in Ball::collideLine(val, vertical, smallsidesolid).
The arguments vlow and vhigh define the extent of the segment in the non-constant coordinate of the line.
*/
bool Ball::collideSegment(int val, bool vertical, bool smallsidesolid, int vlow, int vhigh) {
  int oc = vertical ? y : x;
  if(!(vlow <= oc-BALL_R && oc-BALL_R <= vhigh) && 
     !(vlow <= oc+BALL_R && oc+BALL_R <= vhigh)) {
    return false;
  }


  return collideLine(val, vertical, smallsidesolid);
}

void Ball::collide(Tile &tile) {
  bool havecollided = false;
  havecollided |= collideSegment(tile.getY(), false, false, tile.getX(), tile.getX() + TILE_WIDTH);
  if(havecollided) { tile.takeDamage(); return ; }
  havecollided |= collideSegment(tile.getY() + TILE_HEIGHT, false, true, tile.getX(), tile.getX() + TILE_WIDTH);
  if(havecollided) { tile.takeDamage(); return ; }
  havecollided |= collideSegment(tile.getX(), true, true, tile.getY(), tile.getY() + TILE_HEIGHT);
  if(havecollided) { tile.takeDamage(); return ; }
  havecollided |= collideSegment(tile.getX(), true, false, tile.getY(), tile.getY() + TILE_HEIGHT);
  if(havecollided) { tile.takeDamage(); return ; }
}

void Ball::collideBorders() {
  bool havecollided = false;
  havecollided |= collideLine(0, true, true);
  havecollided |= collideLine(MAXX, true, false);
  havecollided |= collideLine(0, false, true);
  havecollided |= collideLine(MAXY, false, false);
}

void Ball::report() {
  printf("Position (%d %d), direction (%d %d)\n", x, y, dx, dy);
}
