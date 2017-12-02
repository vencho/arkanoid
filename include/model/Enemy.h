#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include<geometry/DockedRectangle.h>
class Enemy : public DockedRectangle {
 private:
  int id;
  const static int ticksPerCurve = 250;
  int ticksOnCurrentCurve;
  int curvesCompleted;
  int xA, yA, xB, yB, xC, yC, xD, yD;
  void generateNewCurve(bool leave);
 public:
  Enemy(int x, int y);
  void tick();
  int getId() const;
};
#endif
