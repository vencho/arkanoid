#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include<geometry/DockedRectangle.h>
#include<model/GameObject.h>
#include<vector>

class Enemy : public DockedRectangle, public GameObject {
 public:
  const static int enemyPhysicalWidth = 25; 
  const static int enemyPhysicalHeight = 30;
 private:
  int ticksOnCurrentCurve;
  int curvesCompleted;
  std::vector<std::pair<int, int>> deBoor;
  std::vector<std::pair<int, int>> bezier;
  bool initialised;
  void generateNewCurve(bool leave);
  void recomputeBezier();
 public:
  Enemy(int x, int y);
  void tick();
};
#endif
