#ifndef GAME_EVENT_MONITOR_H_DEFINED
#define GAME_EVENT_MONITOR_H_DEFINED

#include<model/Enemy.h>
#include<model/Ball.h>
#include<model/Powerup.h>
#include<model/Bullet.h>

class GameEventMonitor {
 public:
  virtual void notifyDied();

  virtual void notifyEnters(const Bullet &bullet);
  virtual void notifyLeaves(const Bullet &bullet);
  virtual void notifyEnters(const Tile &tile);
  virtual void notifyLeaves(const Tile &tile);
  virtual void notifyEnters(const Powerup &powerup);
  virtual void notifyLeaves(const Powerup &powerup);
  virtual void notifyEnters(const Enemy &enemy);
  virtual void notifyLeaves(const Enemy &enemy);
  virtual void notifyLeaves(const Ball &ball);
  virtual void notifyEnters(const Ball &ball);
  virtual void notifyTileHit(const Tile &tile);
};

#endif
