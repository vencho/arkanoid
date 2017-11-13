#ifndef TILE_DESTRUCTION_MONITOR_H_DEFINED
#define TILE_DESTRUCTION_MONITOR_H_DEFINED

class TileDestructionMonitor {
 public:
  virtual void notifyTileDestroyed(int id) = 0;
  virtual void notifyTileHit(int id) = 0;
};

#endif
