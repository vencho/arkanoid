#include<model/Enemy.h>
#include<model/Board.h>
#include<cstdlib>
#include<cstdio>

Enemy::Enemy(int x, int y) : DockedRectangle(x, y, enemyPhysicalWidth, enemyPhysicalHeight) {
  ticksOnCurrentCurve = ticksPerCurve;
  curvesCompleted = 0;
  initialised = false;
  bezier.resize(4);
}

void Enemy::tick() {
  if(!initialised) {
    scaledY += 500;
    if(scaledY > 0) initialised = true;
    return;
  }
  #define x first
  #define y second

  if(ticksOnCurrentCurve == ticksPerCurve) generateNewCurve(false);
  double t = ticksOnCurrentCurve / (double) ticksPerCurve;
  double x = (1-t)*(1-t)*(1-t)*bezier[0].x + 3*(1-t)*(1-t)*t*bezier[1].x + 3*(1-t)*t*t*bezier[2].x + t*t*t*bezier[3].x;
  double y = (1-t)*(1-t)*(1-t)*bezier[0].y + 3*(1-t)*(1-t)*t*bezier[1].y + 3*(1-t)*t*t*bezier[2].y + t*t*t*bezier[3].y;
  scaledX = (int) (x*denominator);
  scaledY = (int) (y*denominator);
  ticksOnCurrentCurve++;
  #undef x
  #undef y
}


void Enemy::recomputeBezier() {
  #define x first
  #define y second
  bezier[0] = std::make_pair( deBoor[0].x / 6 + 2*deBoor[1].x / 3 + deBoor[2].x / 6,
			      deBoor[0].y / 6 + 2*deBoor[1].y / 3 + deBoor[2].y / 6 );

  bezier[1] = std::make_pair( 2*deBoor[1].x / 3 + deBoor[2].x / 3,
			      2*deBoor[1].y / 3 + deBoor[2].y / 3 );

  bezier[2] = std::make_pair( deBoor[1].x / 3 + 2*deBoor[2].x / 3,
			      deBoor[1].y / 3 + 2*deBoor[2].y / 3 );

  bezier[3] = std::make_pair( deBoor[1].x / 6 + 2*deBoor[2].x / 3 + deBoor[3].x / 6,
			      deBoor[1].y / 6 + 2*deBoor[2].y / 3 + deBoor[3].y / 6 );
  #undef x
  #undef y
}

void Enemy::generateNewCurve(bool leave) {
  int x, y;
  ticksOnCurrentCurve = 0;
  if(curvesCompleted != 0) {
    deBoor.erase(deBoor.begin());
  }
  else {
    x = scaledX / denominator;
    y = scaledY / denominator;
    deBoor.push_back(std::make_pair(x - 100, y));
    deBoor.push_back(std::make_pair(x, y));
    deBoor.push_back(std::make_pair(x + 100, y));
  }
  x = rand() % Board::playAreaWidth;
  y = rand() % Board::playAreaHeight;
  deBoor.push_back(std::make_pair(x, y));
  recomputeBezier();
  // printf("%d (%d %d) (%d %d) (%d %d) (%d %d)\n", getId(), xA, yA, xB, yB, xC, yC, xD, yD);
  // xD = Board::playAreaWidth / 2 + (rand() % (Board::playAreaWidth)/2);
  // yD = Board::playAreaHeight / 2 + (rand() % (Board::playAreaHeight)/2);
  curvesCompleted++;
}
