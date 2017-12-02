#include<model/Enemy.h>
#include<model/Board.h>
#include<Global.h>
#include<cstdlib>
#include<cstdio>

Enemy::Enemy(int x, int y) : DockedRectangle(x, y, enemyPhysicalWidth, enemyPhysicalHeight) {
  static int nextId = 0;
  id = nextId++;
  ticksOnCurrentCurve = ticksPerCurve;
  curvesCompleted = 0;
}

int Enemy::getId() const {
  return id;
}

void Enemy::tick() {
  if(ticksOnCurrentCurve == ticksPerCurve) generateNewCurve(false);
  double t = ticksOnCurrentCurve / (double) ticksPerCurve;
  double x = (1-t)*(1-t)*(1-t)*xA + (1-t)*(1-t)*t*xB + (1-t)*t*t*xC + t*t*t*xD;
  double y = (1-t)*(1-t)*(1-t)*yA + (1-t)*(1-t)*t*yB + (1-t)*t*t*yC + t*t*t*yD;
  scaledX = (int) (x*denominator);
  scaledY = (int) (y*denominator);
  ticksOnCurrentCurve++;
}

void Enemy::generateNewCurve(bool leave) {
  ticksOnCurrentCurve = 0;
  if(curvesCompleted != 0) {
    xA = xD;
    yA = yD;
  }
  else {
    xA = scaledX / denominator;
    yA = scaledY / denominator;
  }
  xB = rand() % Board::playAreaWidth;
  xC = rand() % Board::playAreaWidth;
  xD = rand() % Board::playAreaWidth;
  yB = rand() % Board::playAreaHeight;
  yC = rand() % Board::playAreaHeight;
  yD = rand() % Board::playAreaHeight;
  curvesCompleted++;
}
