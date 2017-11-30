#ifndef GAME_EVENT_MONITOR_H_DEFINED
#define GAME_EVENT_MONITOR_H_DEFINED

#include<model/Enemy.h>

class GameEventMonitor {
 public:
  virtual void notifyTileDestroyed(int id);
  virtual void notifyTileHit(int id);
  virtual void notifyPowerupDestroyed(int id);
  virtual void notifyDied();
  virtual void notifyEnemyDestroyed(Enemy &enemy);
};

#endif
